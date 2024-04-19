#include <iostream>
#include "DoubleLinkedList.h"
using namespace std;

int main()
{
    DoubleLinkedList<int> MyList;
    MyList.PushBack(10);
    DoubleLinkedList<int>::Node* node = MyList.PushBack(20);
    MyList.PushBack(30);
    MyList.PushBack(40);   // 추가 테스트
    MyList.Delete(node);    // 삭제 테스트

    // 전체 목록을 출력  반복자 사용은 필수 아님
    DoubleLinkedList<int>::Iterator iter = MyList.Begin();
    for (; iter != MyList.End(); ++iter)
    {
        std::cout << *iter << std::endl;
    }

    return 0;
}