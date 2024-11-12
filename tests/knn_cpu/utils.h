#include <iostream>
#include <vector>
#include <cstdlib>  // for std::abort

#define CUSTOM_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: (" #condition "), function " << __FUNCTION__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << ".\n" \
                      << "Message: " << message << std::endl; \
            std::abort(); \
        } \
    } while (false)

template <typename T>
bool element_in_vector(T item, std::vector<T> vec)
{
    bool is_in = std::find(vec.begin(), vec.end(), item) != vec.end();
    return is_in;
}