// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * Regular expression allow for text management and search of different
 * patterns, for using it in C++, you will need the <regex> header.
 * 
 * If you want to learn about REGEX, you can check:
 *      https://regexr.com/
 * 
 * AS a brief example, for the case of the expression for emails:
 *      ^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$
 * 
 * It is composed by:
 *  ^ : Start of the string
 *  [A-Z0-9._%+-]+ : Min one char A-Z, 0-0 or the symbols -, %, +. (local)
 *  @ : Char @ (at)
 *  [A-Z0-9._%+-]+ : Min one char A-Z, 0-0 or the symbols -, %, +. (host)
 *  \. : Dot (for label separation)
 *  [A-Z]{2,} : DNS label for 2 to 63 chars
 *  $ : End of the string
 * 
 * In the code, we will illustrate just one case of regex, but you may discover
 * others present in the POSIX and stardard libraries. Another commands you can
 * explore are:
 * 
 *  - std::basic_regex : For defining a regex object (char or wchart_t)
 *  - std::sub_match : For matching a capture group, related with std::pair.
 *  - std::match_resuls : Collection of matches for different char array types. 
 *  - std::regex_match : Match an entire string (boolean)
 *  - std::regex_search : For searching in strings the pattern as a part.
 *  - std::regex_replace : If it find the pattern, it will make a replace.
 *  - std::regex_iterator: For searching ocurrences of a pattern in a string.
 *  - std::regex_token_iterator: For iteration on submatching patterns.
 *  
 * NOTE: Do not foget to check online resources to learn more about regular
 * expressions.
 * 
 * You can run this code with:
 * 
 *      g++ -std=c++14 L09_reg_expr.cpp -o regex.out
 *      ./regex.out
 *      
*/

// ------------------------- REQUIRED HEADERS ---------------------------------
#include <regex>   // For using standarized regular expressions in C++
#include <string>  // Managing strings and char arrays
#include <iomanip> // Parametric manipulators for input/output stream

// ----------------------- FUNCTION PROTOTYPES --------------------------------
bool is_valid_email_format(std::string const & email);
void test_email_format(std::string const & email);

// --------------- NAMESPACES, CLASS AND STRUCT  DEFINITIONS ------------------
using namespace std::string_literals;

// ---------------------- MAIN IMPLEMENTATION ---------------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 9: Using regex in your code...\n" << std::endl;

    // Info #1: Creating a simple regular expression.
    auto pattern {R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s};
    auto rx_simple = std::regex{pattern};
    auto rx_full = std::regex{pattern, std::regex_constants::icase};
    auto obj = "gmail@yourdomain.com";
    auto valid = std::regex_match(obj, rx_full);
    std::cout << "Pattern: " << pattern << std::endl
              << "Evaluation: " << obj << " is " <<  valid << std::endl;

    // Info #2: Creating a function to evaluate programs.
    std::cout << "Let's test some email domains: " << std::endl;
    test_email_format("dan@dandomain.com");
    test_email_format("DAN@dandomain.go.co");
    test_email_format("col@mail.co");
    test_email_format("113111@localhost");

    return 0;

} // main

// ---------------------- FUNCTION DEFINITIONS --------------------------------

/**
 * Check with regular expressions if the email is valid.
 * 
 * @param email String with the email to evaluate
 * 
 * @return True if the format match, False otherwise.
*/
bool is_valid_email_format(std::string const & email)
{
    auto eval {R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s};
    auto regex = std::regex{eval, std::regex_constants::icase};
    return std::regex_match(email, regex);
}

/**
 * Display the evaluation result of the format of a provided email.
 * 
 * @param email String with the email to consider.
*/
void test_email_format(std::string const & email)
{
    std::cout <<  std::setw(20) << std::left
               << "Email (" << email << ") is "
               << (is_valid_email_format(email) ? "valid" : "invalid")
               << std::endl;
}