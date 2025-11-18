// ---------------------------- REQUIRED LIBRARIES ----------------------------
#include <iostream>  // Common I/O stream
#include <fstream>   // For files as I/O streams
#include <string>    // For arrays of characters and their utilities
#include <utility>   // Oriented to the usage of std::move, std::forward

// ------------------------- CLASS DEFINITIONS --------------------------------

/**
 * Class for manage and handle file.
 */
class FileHandle
{
public:
    /**
     * Constructor implementation
     *
     * @param filename Path to the file to open
     */
    explicit FileHandle(const std::string& filename)
        : file_(filename)
    {
        std::cout << "[FileHandle] Opening file: " << filename << "\n";
    }

    // Destructor implementation

    ~FileHandle() {
        std::cout << "[FileHandle] Closing file\n";
        file_.close();
    }

    // Avoid copy implementation (not recommended for files)

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // Include move constructor

    FileHandle(FileHandle&& other) noexcept
        : file_(std::move(other.file_))
    {
        std::cout << "[FileHandle] Move constructing\n";
    }

    /**
     * Output stream return
     */
    std::ofstream& stream() { return file_; }

private:
    // File output stream to consider
    std::ofstream file_;
};

/**
 * Logger class to display info of a file management
 */
class Logger {
public:
    /**
     * Constructor for a logger
     *
     * @param fh File handler element.
     */
    explicit Logger(FileHandle fh)
        : file_(std::move(fh))  // move resource INTO this object
    {
        std::cout << "[Logger] Constructed\n";
    }

    // Destructor implementation

    ~Logger()
    {
        std::cout << "[Logger] Destroyed\n";
    }

    /**
     * Create a log message
     *
     * @param msg Content to display
     */
    void log(const std::string& msg)
    {
        file_.stream() << msg << "\n";
    }

private:
    FileHandle file_;
};

// -------------------------- FUNCTION DECLARATIONS ---------------------------

/**
 * Common wrapper to create a forwarding implementation, so it ensures
 * lvalue as lvalue and rvalue as rvalue.
 *
 * @param args Generic object to be forwarded on init.
 *
 * @return Return created object
 */
template <typename T, typename... Args>
T make_object(Args&&... args)
{

    return T(std::forward<Args>(args)...);
}

/**
 * Specifies if object was managed as lvalue.
 *
 * @param s String considered
 */
void handle_string(std::string& s)
{
    std::cout << "handle_string(lvalue): " << s << "\n";
}

/**
 * Specifies if object was managed as rvalue.
 *
 * @param s String considered
 */
void handle_string(std::string&& s)
{
    std::cout << "handle_string(rvalue): " << s << "\n";
}

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main()
{
    // lifetime management
    std::cout << "\n--- Creating Logger ---\n";
    std::cout << "\n";

    Logger logger = make_object<Logger>(
        make_object<FileHandle>("log.txt")
    );
    std::cout << "\n";
    logger.log("This is a test log entry.");

    // rvalue vs lvalue demo
    std::string name = "Felipe";
    handle_string(name);
    handle_string("Felipe");
    std::cout << "\n";

    // forces rvalue with std::move
    handle_string(std::move(name));  // forces rvalue overload
    std::cout << "\n";

    // Lambda implementation case
    auto produce_message = []() {
        std::string msg = "Produced message";
        return msg;
    };

    std::string msg = produce_message();
    logger.log(msg);
    std::cout << "\n";

    std::cout << "--- End of program ---\n";
    std::cout << "\n";
    return 0;
}
