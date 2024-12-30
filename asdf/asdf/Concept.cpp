#include <iostream>
#include <type_traits>
#include <concepts>

template <typename T>
concept NUMBERS = std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double>;

template <NUMBERS T>
T AddNUM(T a, T b) {
    return a + b;
}


//lessthen 8

template <class T>
concept LessThen8 = sizeof(T) < 8;

template <class T> requires LessThen8<T>
void foo(T arg) {
    std::cout << typeid(T).name() <<" is size of Less then 8" << std::endl;
}

template <class T>
void foo(T arg) {
    std::cout << typeid(T).name() << " is size " << sizeof(T) << std::endl;
}

template <typename T>
concept INT = std::is_same<T, int>::value;

template <typename T>
concept INTORLONG = std::is_same<T, int>::value || std::is_same<T, long>::value;

//template <typename T> requires std::is_same<T, int>::value
template <typename T> requires 
INT<T> || 
INTORLONG<T>
int increase(T a) {
    return a + 1;
}

//template <typename T>
//concept Integer = std::is_convertible_v<T, int>;
//
//template <Integer T1, Integer T2>
//long long Add(T1 a, T2 b) {
//    return a + b;
//}

class MyClass {
public:
    using value_type = int;
};


template <typename T>
concept HasValueType = requires{
    typename T::value_type;
};


template <HasValueType T> class A {};

template <class T>
concept Equality = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

template <class T>
concept Container = requires(T a) {
    a.begin();
    a.end();
};

template <class T>
concept Integeral = std::is_integral_v<T>;

template <class T,typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

template <typename T>
concept IsPrintable = std::integral<T> || std::floating_point<T> ||
IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;

void println(IsPrintable auto const ... arguments) {
    (std::wcout << ... << arguments) << '\n';
}

template <typename T>
concept INTORFLOAT = std::same_as<T, int> || std::same_as<T, float>;

void print_int_float(INTORFLOAT auto const value) {
    std::cout << value << std::endl;
}


class Player {};
class Monster :public Player {};

template <typename T>
concept PlayerType = std::derived_from<T, Player>;

void funcPlayer(PlayerType auto a) {
    std::cout << "funcPlayer();" << std::endl;
}


int main() {

    A<MyClass> a;
  
    //std::cout << AddNUM<float>(1.2, 2) << std::endl;

    /*int i = 10;
    short s = 10;
    double d = 3.14;

    foo(i);
    foo(s); 
    foo(d); */

    std::cout << increase(1) << std::endl;
    
    //std::cout << increase(1.0) << std::endl; // error

    bool result = Integeral<int>;

    //INTORFLOAT
    print_int_float(1);
    print_int_float(1.2f);
    //print_int_float(1.5);
    //print_int_float(10L);
 
    funcPlayer(Player());
    funcPlayer(Monster());
    //funcPlayer(1.5);

    return 0;
};