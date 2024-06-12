//# Lesson2.무엇이 효율적인가 ?
//
//게임인재원 자료구조와 알고리즘 수업을 위한 자료  2024.0612
//
//> Notice
//>
//>
//> 샘플 코드는 코드를 읽고 결과를 예상해 본 후에 컴파일해서 확인해 봅시다.
//> 연습 문제는 수업 시간에  학생 1명을 지목해서 확인 합니다. (Discode 화면 공유 및 설명)
//> 과제는 제시한 파일명으로 작성 후, svn 으로 제출합니다.
//>
//

#include <iostream>

//** [연습 문제 1] 배열에서 최대 값 찾기**
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
//** [샘플 코드] stl::array vs  stl::vector**
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

    //arr2[10] = 11; //Is OK? ^^a //함수에 잘못된 매개 변수가 전달

    arr2.push_back(12); //Is OK? YES!!!!

    std::cout << "arr2.size() " << arr2.size() << std::endl;
    std::cout << "arr2.capacity() " << arr2.capacity() << std::endl;


    return 0;
}

//```
//
//Q.어떤 차이점이 있나요 ?
// array는 maxsize를 정하여 놓고 maxsize 이상의 내용을 담을 수 없다 //스택영역에 할당
// vector는 capacity 이상의 내용을 추가 할경우 capacity의 크기를 늘린다. //힙영역에 할당
// 
//Q.어떤 공통점이 있나요 ?
// 배열로서 인덱스 접근이 가능하고 메모리에 선형적인 구조를 가진다.
//
#include <iostream>
#include <array>
#include <vector>
//**[샘플 코드] Vector 의 Capacity 확인 * *
//
//```cpp
int main()
{
    std::vector<int> arr3;
    int prev = arr3.capacity();
    int next = prev;
    for (int i = 0; i < 100; i++)
    {
        arr3.push_back(i); // 하나씩 넣으면서 capacity가 어떻게 변하는지 확인해보자.

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
//Q.Capacity 가 어떤 규칙에 따라 증가하는 것 같나요 ?
// 1,1,1,2,3,4,6,9,14,21,31,47
// 
//-STL 구현 내용을 살펴 봅시다.
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
//** [연습 문제 2] 배열에서 최대 값 찾기 연습 문제에서  std::array or std::vector 사용으로 수정 * *
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
//**[샘플 코드] deque * *
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
//    -deque 도 vector 처럼 메모리 동적 할당을 합니다.어떤 growth 규칙을 가지고 있을까요 ?
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
//** [연습 문제 3] 스택에서 최대 값 찾기**
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

    // 입력 받은 숫자들을 순서대로 스택에 넣고 최대 값을 찾아 출력하세요.
    // 예) 1 2 3 4 5 입력시 5 출력
    // Hint: 최대값을 찾기 위한 스택을 하나 더 사용할 수 있습니다.
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
    // 일단, 시도 하세요.
    // 다음 수업 시간에 함께 풀어 봅니다.

    return 0;
}
//```
//
//** [연습 문제 4] 괄호 검사 문제(스택 활용)**
//
//        > 괄호의 우선 순위는 없습니다.괄호 외의 다른 문자는 무시 합니다.
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

    // 괄호의 짝이 맞는지 확인하세요.
    // 예) "()" => true, "()[]{}" => true, "(]" => false, "([)]" => false, "{[]}" => true
    // Hint: 스택을 사용하세요.
    // 일단, 시도 하세. 다음 시간에 함께 풀어 봅시다.
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
//[하노이의 탑](https://www.notion.so/51b7a965ff194c06a389f396f412b2d7?pvs=21)s