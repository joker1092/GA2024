#include <iostream>
#include <algorithm>
#include <vector>


template <typename T>
void negate_all(std::vector<T>& v) {
     for_each(v.begin(), v.end(), [](T& a) {
        a = -a;
        });
}


int main()
{
    std::vector<int> v1 = { 1,2,3,4,5,6,7,8,9,10 };
    std::vector<long> v2 = { 1L,2L,3L,4L,5L,6L,7L,8L,9L,10L };
    
    negate_all<int>(v1);

    negate_all<long>(v2);

    for (auto i : v1)
    {
        std::cout << i << " ";
    }
    
    std::cout << std::endl;

    for (auto i : v2)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

}
