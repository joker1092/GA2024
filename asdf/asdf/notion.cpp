//# Lesson2.������ ȿ�����ΰ� ?
//
//��������� �ڷᱸ���� �˰��� ������ ���� �ڷ�  2024.0612
//
//> Notice
//>
//>
//> ���� �ڵ�� �ڵ带 �а� ����� ������ �� �Ŀ� �������ؼ� Ȯ���� ���ô�.
//> ���� ������ ���� �ð���  �л� 1���� �����ؼ� Ȯ�� �մϴ�. (Discode ȭ�� ���� �� ����)
//> ������ ������ ���ϸ����� �ۼ� ��, svn ���� �����մϴ�.
//>
//

#include <iostream>

//** [���� ���� 1] �迭���� �ִ� �� ã��**
//
//```cpp
#include <iostream>

int FindMax(const int* arr, const int size)
{
    int max = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

int main()
{
    int arr[10] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };

    std::cout << "Max: " << FindMax(arr, 10) << std::endl;

    return 0;
}
//```
//
//** [���� �ڵ�] stl::array vs  stl::vector**
//
//```cpp
#include <iostream>
#include <array>
#include <vector>

int main()
{
    std::array<int, 10> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> arr2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << "arr max size " << arr.max_size() << std::endl;

    //arr[10]= 11; //Is OK? ^^a //array subscript out of range

    std::cout << "arr2 max size " << arr2.max_size() << std::endl;
    std::cout << "arr2.size() " << arr2.size() << std::endl;
    std::cout << "arr2.capacity() " << arr2.capacity() << std::endl;

    //arr2[10] = 11; //Is OK? ^^a //�Լ��� �߸��� �Ű� ������ ����

    arr2.push_back(12); //Is OK? YES!!!!

    std::cout << "arr2.size() " << arr2.size() << std::endl;
    std::cout << "arr2.capacity() " << arr2.capacity() << std::endl;


    return 0;
}

//```
//
//Q.� �������� �ֳ��� ?
// array�� maxsize�� ���Ͽ� ���� maxsize �̻��� ������ ���� �� ���� //���ÿ����� �Ҵ�
// vector�� capacity �̻��� ������ �߰� �Ұ�� capacity�� ũ�⸦ �ø���. //�������� �Ҵ�
// 
//Q.� �������� �ֳ��� ?
// �迭�μ� �ε��� ������ �����ϰ� �޸𸮿� �������� ������ ������.
//
#include <iostream>
#include <array>
#include <vector>
//**[���� �ڵ�] Vector �� Capacity Ȯ�� * *
//
//```cpp
int main()
{
    std::vector<int> arr3;
    int prev = arr3.capacity();
    int next = prev;
    for (int i = 0; i < 100; i++)
    {
        arr3.push_back(i); // �ϳ��� �����鼭 capacity�� ��� ���ϴ��� Ȯ���غ���.

        next = arr3.capacity();
        if (prev != next)
        {
            std::cout << "arr3 size " << arr3.size() << " capacity() " << next << std::endl;
            prev = next;
        }
    }

    return 0;
}
//```
//
//Q.Capacity �� � ��Ģ�� ���� �����ϴ� �� ������ ?
// 1,1,1,2,3,4,6,9,14,21,31,47
// 
//-STL ���� ������ ���� ���ô�.
// 
// 
//
//CONSTEXPR20 size_type _Calculate_growth(const size_type _Newsize) const {
//    // given _Oldcapacity and _Newsize, calculate geometric growth
//    const size_type _Oldcapacity = capacity();
//    const auto _Max = max_size();
//
//    if (_Oldcapacity > _Max - _Oldcapacity / 2) {
//        return _Max; // geometric growth would overflow
//    }
//
//    const size_type _Geometric = _Oldcapacity + _Oldcapacity / 2;
//
//    if (_Geometric < _Newsize) {
//        return _Newsize; // geometric growth would be insufficient
//    }
//
//    return _Geometric; // geometric growth is sufficient
//}
//```
//
//
//** [���� ���� 2] �迭���� �ִ� �� ã�� ���� ��������  std::array or std::vector ������� ���� * *
//
 int FindMax(std::vector<int> arr)
{

    std::vector<int>::iterator iter;
    iter = arr.begin();

    int max = *iter;

    for (iter = arr.begin(); iter != arr.end(); iter++)
    {
        if (max < *iter)
        {
            max = *iter;
        }
    }

    return max;
}

int main()
{
    std::vector<int> arr = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };

    std::cout << "Max: " << FindMax(arr) << std::endl;

    return 0;
}
// 
//**[���� �ڵ�] deque * *
//
//```cpp
int main()
{
    std::deque<int> deq = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << deq.max_size() << std::endl;
    std::cout << deq.size() << std::endl;

    deq.push_front(0);
    deq.push_back(11);

    std::cout << deq.size() << std::endl;

    for (auto iter = deq.begin(); iter != deq.end(); ++iter)
    {
        std::cout << *iter << " ";
    }

    return 0;
}
//```
//
//![[c++ - What really is a deque in STL ? -Stack Overflow](https://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl/6292437#6292437)](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ac6a158-21bd-4bc3-b86f-a1b6941638a4/9a55e27b-c55f-4d7b-acea-5b9ac156dffa/Untitled.png)
//
//[c++ - What really is a deque in STL ? -Stack Overflow] (https ://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl/6292437#6292437)
//
//    -deque �� vector ó�� �޸� ���� �Ҵ��� �մϴ�.� growth ��Ģ�� ������ ������� ?
//
//    ```cpp
void _Growmap(size_type _Count) { // grow map by at least _Count pointers, _Mapsize() a power of 2
    static_assert(_Minimum_map_size > 1, "The _Xlen() test should always be performed.");

    _Alpty _Almap(_Getal());
    size_type _Newsize = _Mapsize() > 0 ? _Mapsize() : 1;
    while (_Newsize - _Mapsize() < _Count || _Newsize < _Minimum_map_size) {
        // scale _Newsize to 2^N >= _Mapsize() + _Count
        if (max_size() / _Block_size - _Newsize < _Newsize) {
            _Xlen(); // result too long
        }

        _Newsize *= 2;
    }

    size_type _Myboff = _Myoff() / _Block_size;
    _Mapptr _Newmap = _Allocate_at_least_helper(_Almap, _Newsize);
    _Mapptr _Myptr = _Newmap + _Myboff;

    _Count = _Newsize - _Mapsize();

    _Myptr = _STD uninitialized_copy(_Map() + _Myboff, _Map() + _Mapsize(), _Myptr); // copy initial to end
    if (_Myboff <= _Count) { // increment greater than offset of initial block
        _Myptr = _STD uninitialized_copy(_Map(), _Map() + _Myboff, _Myptr); // copy rest of old
        _Uninitialized_value_construct_n_unchecked1(_Myptr, _Count - _Myboff); // clear suffix of new
        _Uninitialized_value_construct_n_unchecked1(_Newmap, _Myboff); // clear prefix of new
    }
    else { // increment not greater than offset of initial block
        _STD uninitialized_copy(_Map(), _Map() + _Count, _Myptr); // copy more old
        _Myptr = _STD uninitialized_copy(_Map() + _Count, _Map() + _Myboff, _Newmap); // copy rest of old
        _Uninitialized_value_construct_n_unchecked1(_Myptr, _Count); // clear rest to initial block
    }

    if (_Map() != nullptr) {
        _Destroy_range(_Map(), _Map() + _Mapsize());
        _Almap.deallocate(_Map(), _Mapsize()); // free storage for old
    }

    _Map() = _Newmap; // point at new
    _Mapsize() += _Count;
}
//```
//
//
//** [���� ���� 3] ���ÿ��� �ִ� �� ã��**
//
//```cpp
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <stack>

int main()
{
    std::string input;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    std::stringstream ss(input);

    std::string word;
    std::stack<int> numbers;
    while (ss >> word)
    {
        numbers.push(std::stoi(word));
    }

    // �Է� ���� ���ڵ��� ������� ���ÿ� �ְ� �ִ� ���� ã�� ����ϼ���.
    // ��) 1 2 3 4 5 �Է½� 5 ���
    // Hint: �ִ밪�� ã�� ���� ������ �ϳ� �� ����� �� �ֽ��ϴ�.
    int max = 0;
    while (!numbers.empty())
    {
        if (numbers.top() > max)
        {
            max = numbers.top();
        }
        numbers.pop();
    }

    std::cout << max << std::endl;
    // Implement here
    // �ϴ�, �õ� �ϼ���.
    // ���� ���� �ð��� �Բ� Ǯ�� ���ϴ�.

    return 0;
}
//```
//
//** [���� ���� 4] ��ȣ �˻� ����(���� Ȱ��)**
//
//        > ��ȣ�� �켱 ������ �����ϴ�.��ȣ ���� �ٸ� ���ڴ� ���� �մϴ�.
//    >
//    >
//> () { }[]         O.K
//> [{ () }]         O.K
//> [{ (}]          O.K
//> [}                 Error
//> [{                  Error
//>
//> ```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <stack>

bool CheckValidParentheses(const std::string& s)
{
    std::stack<char> Parent;

    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            Parent.push(s[i]);
        }
        if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            if (!Parent.empty())
            {
                if (s[i] == ')')
                {
                    if (Parent.top() == '(')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }

                }
                else if (s[i] == '}')
                {
                    if (Parent.top() == '{')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (s[i] == ']')
                {
                    if (Parent.top() == '[')
                    {
                        Parent.pop();
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else {
                return false;
            }
        }
    }

    if (Parent.empty())
    {
        return true;
    }

    // ��ȣ�� ¦�� �´��� Ȯ���ϼ���.
    // ��) "()" => true, "()[]{}" => true, "(]" => false, "([)]" => false, "{[]}" => true
    // Hint: ������ ����ϼ���.
    // �ϴ�, �õ� �ϼ�. ���� �ð��� �Բ� Ǯ�� ���ô�.
    return false;
}

int main()
{
    std::string input;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    // Valid Parentheses
    std::cout << "Valid Parentheses: " << CheckValidParentheses(input) << std::endl;

    return 0;
}
//>
//
//[�ϳ����� ž](https://www.notion.so/51b7a965ff194c06a389f396f412b2d7?pvs=21)s