#include <iostream>     // For std::cout
#include <limits>       // For std::numeric_limits
#include <typeinfo>     // For typeid
#include <tuple>        // For std::pair

// Modified add_numbers function to detect overflow
template <typename T>
std::pair<bool, T> add_numbers(T const &start, T const &increment, unsigned long int const &steps) {
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i) {
        // Check for overflow
        if (result > std::numeric_limits<T>::max() - increment) {
            return {false, result}; // Overflow detected
        }
        result += increment;
    }
    return {true, result}; // No overflow
}

// Modified subtract_numbers function to detect underflow
template <typename T>
std::pair<bool, T> subtract_numbers(T const &start, T const &decrement, unsigned long int const &steps) {
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i) {
        // Check for underflow
        if (result < std::numeric_limits<T>::min() + decrement) {
            return {false, result}; // Underflow detected
        }
        result -= decrement;
    }
    return {true, result}; // No underflow
}

// Adjusted test_overflow function to handle overflow messages
template <typename T>
void test_overflow() {
    const unsigned long int steps = 5;
    const T increment = std::numeric_limits<T>::max() / steps;
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;

    auto add_result = add_numbers<T>(start, increment, steps);
    if (add_result.first) {
        std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = " << +add_result.second << std::endl;
    } else {
        std::cout << "\tOverflow detected!" << std::endl;
    }

    add_result = add_numbers<T>(start, increment, steps + 1);
    if (add_result.first) {
        std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = " << +add_result.second << std::endl;
    } else {
        std::cout << "\tOverflow detected!" << std::endl;
    }
}

// Adjusted test_underflow function to handle underflow messages
template <typename T>
void test_underflow() {
    const unsigned long int steps = 5;
    const T decrement = std::numeric_limits<T>::max() / steps;
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;

    auto subtract_result = subtract_numbers<T>(start, decrement, steps);
    if (subtract_result.first) {
        std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = " << +subtract_result.second << std::endl;
    } else {
        std::cout << "\tUnderflow detected!" << std::endl;
    }

    subtract_result = subtract_numbers<T>(start, decrement, steps + 1);
    if (subtract_result.first) {
        std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = " << +subtract_result.second << std::endl;
    } else {
        std::cout << "\tUnderflow detected!" << std::endl;
    }
}

void do_overflow_tests(const std::string &star_line) {
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Signed integers
    test_overflow<char>();
    test_overflow<short>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // Unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // Floating point types
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string &star_line) {
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Signed integers
    test_underflow<char>();
    test_underflow<short>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // Unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // Floating point types
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

// Entry point into the application
int main() {
    std::cout << "Program started!" << std::endl;
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // Run the overflow tests
    std::cout << "Running overflow tests..." << std::endl;
    do_overflow_tests(star_line);

    // Run the underflow tests
    std::cout << "Running underflow tests..." << std::endl;
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}
