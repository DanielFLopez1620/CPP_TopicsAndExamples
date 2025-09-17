#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <numeric>
#include <algorithm>
#include <execution>
#include <chrono>
#include <stdexcept>
#include <stop_token>

std::mutex inventory_mutex;           // Protect shared inventory
std::condition_variable order_ready; // Notify shipping department
std::atomic<int> packed_orders{0};   // Atomic counter
bool has_orders_to_ship = false;     // Shared flag (protected by mutex)
std::vector<int> inventory = {100, 200, 150, 80}; // Stock of items

// Function to pack orders (simulates warehouse worker)
void pack_orders(int worker_id, std::stop_token st) {
    try {
        while (!st.stop_requested()) {
            {
                std::scoped_lock lock(inventory_mutex); // Lock inventory safely
                if (inventory[worker_id % inventory.size()] > 0) {
                    inventory[worker_id % inventory.size()] -= 1;
                    packed_orders++;
                    std::cout << "Worker " << worker_id << " packed an order.\n";
                    has_orders_to_ship = true;
                } else {
                    throw std::runtime_error("Item out of stock!");
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Worker " << worker_id << " error: " << e.what() << "\n";
    }
}

// Function to ship orders (runs in separate thread)
void ship_orders() {
    std::unique_lock lock(inventory_mutex);
    order_ready.wait(lock, [] { return has_orders_to_ship; });
    std::cout << "Shipping department: Orders are being shipped!\n";
    has_orders_to_ship = false;
}

// Async function for discount calculation
int calculate_discount_async(const std::vector<int>& prices) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate delay
    return std::reduce(prices.begin(), prices.end()) / 10; // Simple discount rule
}

int main() {
    std::cout << "Warehouse starting operations...\n";

    // Start packing threads with cancellation support
    std::stop_source stop_source;
    std::vector<std::jthread> workers;
    for (int i = 0; i < 4; ++i) {
        workers.emplace_back(pack_orders, i, stop_source.get_token());
    }

    // Shipping department in another thread
    std::thread shipping(ship_orders);

    // Use a promise/future to signal when a VIP order is ready
    std::promise<std::string> vip_promise;
    std::future<std::string> vip_future = vip_promise.get_future();

    std::thread vip_thread([&vip_promise] {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        vip_promise.set_value("VIP Order Packed and Ready!");
    });

    // Async discount calculation
    std::vector<int> prices = {100, 150, 200, 250};
    auto discount_future = std::async(std::launch::async, calculate_discount_async, prices);

    // Parallel map (apply tax) and fold (sum)
    std::for_each(std::execution::par, prices.begin(), prices.end(), [](int &p) { p += p * 0.19; });
    int total_value = std::reduce(std::execution::par, prices.begin(), prices.end());

    // Simulate a delay and then request cancellation
    std::this_thread::sleep_for(std::chrono::seconds(3));
    stop_source.request_stop(); // Cancel workers

    // Notify shipping department
    order_ready.notify_one();

    // Wait for joinable threads
    if (shipping.joinable()) shipping.join();
    if (vip_thread.joinable()) vip_thread.join();

    // Display results
    std::cout << "VIP Message: " << vip_future.get() << "\n";
    std::cout << "Discount: " << discount_future.get() << "\n";
    std::cout << "Total stock value after tax: " << total_value << "\n";
    std::cout << "Orders packed: " << packed_orders.load() << "\n";

    std::cout << "Warehouse operations complete.\n";
}
