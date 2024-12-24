#include <iostream>
#include <type_traits>


template<typename T>
void tell_type() {
    if (is_void<T>::value)
    {
        std::cout << "T ´Â void! \n";
    }
    else
    {
        std::cout << "T ´Â void °¡ ¾Æ´Ô! \n";
    }
}

int main()
{
    tell_type<int>();
    tell_type<void>();
    return 0;
}