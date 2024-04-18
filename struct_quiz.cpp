//#include <iostream>
//using namespace std;
//
//int main() { 
//}


1. 다음 True / False 문제에 답하라.

가.포인터 변수는 구조체 변수다. 					                (X)
나.포인터 변수는 레코드 타입의 변수만 가리킬 수 있다. 			    (X)
다.C++에서 new p; delete p; 이후에 p의 값은 자동으로 널이 된다. 	(X)


2. 배열 int A[10][10]의 시작 주소(Base Address)가 100이라고 할 때, A[5][6]의 시작 주소는 몇 번지인가 ?
단, 이 시스템에서 정수는 4바이트에 저장하며, 행 우선 순서(Row Major Order)로 배열을 저장한다.

가. 100          나. 156          다. 224          라. 324

라. 324;


3. 문자(char) 타입을 1바이트에, 정수(int) 타입을 4바이트에, 부동소수(double) 타입을 8바이트에 저장하는 시스템에서
다음 구조체 변수 s의 시작 주소를 100번지라고 할 때, s.StudentName.First[0]의 시작 주소는 몇 번지인가 ?

struct Name
{
    char First[20];
    char Middle[2];
    char Last[20];
};
struct Student
{
    Name StudentName;
    int Age;
    double GPA;
} s;

가. 100          나. 112          다. 120          라. 132
가. 100;

4. 다음 프로그램의 출력 결과는 얼마인지 선택하라.

void Average(int x, int y)
{
    int avg = 0;
    avg = (x + y) / 2;
}
int main()
{
    int avg = 3;
    Average(4, 6);
    cout << avg;
}

가. 0          나. 3          다. 4          라. 5

나. 3;

5. 다음 중 for (i = 0; i < 10; i++) n += i; 와 효과가 동일한 것은 무엇인가 ?

 가. while (i > 0) { n += i; } i = 10;
 나.i = 0; while (i < 10) { n += i; i++; }
 다.i = 0; while (i < 10) { i++; n += i; }
 라.i = 0; do { n += i; } while (i < 10);

 나.i = 0; while (i < 10) { n += i; i++; };

6. 다음 명령문 중 포인터 p에 의해 변수 i에 0을 할당하는 것은 무엇인가 ?

 가. int i, * p = i, * p = 0;
 나. int i, * p = &i, * p = 0;
 다. int i, * p = i, p = 0;
 라. int i, * p = &i, p = 0;

 나. int i, * p = &i, * p = 0;


7. int* p; int i; int k; i = 42; k = i; p = &i; 라는 명령문을 순차적으로 실행한다고 하자.
실행 이후에 다음 중 어떤 명령문이 i의 값을 75로 할당하겠는가 ? 맞는 것을 모두 골라라.

가.k = 75;          나.* k = 75;          다.p = 75;          라.* p = 75;

라.*p = 75;

8. 다음 명령의 실행 결과는 무엇인가 ?

int i = 1; int k = 2; int* p1; int* p2;
p1 = &i; p2 = &k; p1 = p2; *p1 = 3; *p2 = 4;
cout << i;

가. 1          나. 2          다. 3          라. 4

라. 4;

9. 동적 변수가 저장되는 공간은 어디인가 ?

가.코드 세그먼트          나.데이터 세그먼트          다.힙          라.실행 스택

다.힙;


10. int x[10]; void CallMe(int z[]); 로 선언되어 있을 때,
x를 인수(Argument)로 하여 CallMe 함수를 호출하는 옳은 방법은 무엇인가 ?

가.CallMe(x);
나.CallMe(x[]);
다.CallMe(x[10]);
라.CallMe(&x);
마.CallMe(&x[]);

가.CallMe(x);


11. 다음 코드의 실행 결과 'X'를 출력하지 않는 명령어는 어떤 것인가 ?
struct charNode
{
    char ch;
    charNode* p;
};

int main(void) {

    charNode* head, * next1;
    char charout = 'Y';
    head = new charNode;
    head->ch = 'X';
    head->p = NULL;
    next1 = head;
    charout = next1->ch;

    return 0;
}

가.cout << (*next1).ch;
나.cout << charout;
다.cout << charNode.ch;
라.cout << head->ch;

다.cout << charNode.ch;

12. 다음 코드의 실행 결과, 'X'를 가진 구조체가 'Z'를 포함한 구조체를 가리키게 하는 명령은 무엇인가 ?

struct charNode
{
    char ch;
    charNode* p;
};

int main(void) {

    charNode* head, * next1, * next2;
    head = new charNode; head->ch = 'X'; next1 = head;
    next2 = new charNode; next2->ch = 'Z'; next1->p = NULL;
}

가.next2->p = head;
나.head->ch = next2;
다.head->p = NULL;
라.next1->p = next2;

라.next1->p = next2;


13. 개에 관한 다음 필드 정보를 저장하기 위한 구조체를 선언하라.
가.이름을 저장하기 위한 문자열 필드(20캐릭터)
나.암수(Female, Male) 구분을 위해 'F' 또는 'M' 을 저장하기 위한 필드
다.개의 품종을 저장하기 위한 문자열 필드(20 캐릭터)
라.나이를 저장하기 위한 정수 필드

struct Dog {
    char name[20];
    char kind[20];
    char sex;
    int age;
};


14. 신입생 개인정보는 학번(StudentNumber), 이름(Name), 나이(Age) 등으로 구성되어 있다.
이러한 신입생 5, 000명에 대한 정보처리가 필요하다고 가정할 때,
이들 모두의 개인정보를 담을 수 있는 자료형 또는 자료구조를 선언하라.

struct Student {
    int StudentNumber;
    int age;
    char name[20];
};

15. strcpy(string1, string2) 함수는 string2 변수의 문자열을 string1 변수로 복사하는 함수다.
이 경우, string1, string2는 배열명이면서 동시에 배열의 첫 요소를 가리키는 포인터로 볼 수 있다.
완전한 strcpy(string1, string2) 함수를 작성하라.

void strcpy(char* string1, char* string2) {
    int i = 0;
    while (string2[i] != '\0') {
        string1[i] = string2[i];
        i++;
    }
    string1[i] = '\0';
}