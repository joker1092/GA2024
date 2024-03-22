#include <iostream>
using namespace std;

int main()
{
    return 0;
}

/*
//1. 입력 받은 수가, 19보다 크거나 같으면 "1", 아니면 "0"을 출력 하세요. (if else 사용)
    int inputA = 0;
    cin >> inputA;
    if (inputA > 19)
    {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }

//2. 입력 받은 수가, 90이상이면 "A", 80이상이면 "B", 70이상이면 "C", 아니면 "F"를 출력하세요. (else if 문)

    int inputB = 0;
    cin >> inputB;
    if (inputB>=90)
    {
        cout << "A" << endl;
    }
    else if (inputB >= 80) {
        cout << "B" << endl;
    }
    else if (inputB >= 70) {
        cout << "C" << endl;
    }
    else {
        cout << "F" << endl;
    }

//3. 입력 받은 수가, 1, 이면 "Excellent", 2혹은 3이면 "Great", 아니면 "Good"을 출력하세요. (switch case문)

    int inputC = 0;
    cin >> inputC;
    switch (inputC)
    {
    case 1:
        cout << "Excellent" << endl;
        break;
    case 2:
        cout << "Great" << endl;
        break;
    case 3:
        cout << "Great" << endl;
        break;
    default:
        cout << "Good" << endl;
        break;
    }


//4. 입력 받은 수가 0보다 작으면 종료하고, 아니면 계속 입력받아 출력하는 코드를 작성하세요 (while 문 사용)

    while (true)
    {
        int inputD = 0;
        cin >> inputD;
        if (inputD < 0)
        {
            break;
        }
        cout << inputD << endl;
    }

//5. 1부터 10 출력하기, 10부터 1 출력하기 (for 문 사용)

    for (size_t i = 1; i <= 10; i++)
    {
        cout << i << endl;
    }

//6. 1부터 100까지 모두 더하기 (for 문 사용)

    int sum = 0;
    for (size_t i = 1; i <= 100; i++)
    {
        sum += i;
    }
    cout << sum;

//7. 구구단 3단 출력하기 (while 문 사용)

    int num = 1;
    while (num<10)
    {
        cout << 3 << "*" << num << "=" << 3 * num << endl;
        num++;
    }

//8. 구구단 2단부터 9단 출력하기 (이중 for 문 사용)

    for (size_t i = 2; i < 10; i++)
    {
        for (size_t j = 1; j < 10; j++)
        {
            cout << i << "*" << j << "=" << i * j << endl;
        }
    }

//9. 1부터 10까지 수에서, 5이하만 출력하기 (break)

    for (size_t i = 1; i <= 10; i++)
    {
        if (i>5)
        {
            break;
        }
        cout << i << endl;
    }

//10. 1부터 10까지 수에서 짝수 출력하기 (continue 사용)

    for (size_t i = 1; i <= 10; i++)
    {
        if (i%2!=0)
        {
            continue;
        }
        cout << i << endl;
    }


//11. 1부터 10까지 수에서 짝수 출력하기 (if나 continue 쓰지 않고 작성)      //
    
    for (size_t i = 2; i <= 10; i+=2)
    {
        cout << i;
    }

//12. 교환 – 두개의 변수를 선언하고 두 변수의 값을 서로 바꾸어 출력해보세요.

    int a = 10, b = 30;
    int temp;

    temp = a;
    a = b;
    b = temp;

    cout << a << b << endl;


//13. 비교 – 두 수를 입력 받아, 큰 수를 출력하세요.
    
    int a = 0, b = 0;
    cin >> a >> b;
    if (a>b)
    {
        cout << a;
    }
    else if (b > a) {
        cout << b;
    }
    else {
        cout << "a==b" << endl;
    }

//14. 배수 - 1~100 사이 수중에서, 13의 배수는 몇개인지 출력하세요.

    int count = 0;
    for (size_t i = 1; i <= 100; i++)
    {
        if (i % 13 == 0) {
            count++;
        }
    }
    cout << count;

//15. 절대값 – 정수를 입력 받아, 절대값을 출력하세요.

    int inNum = 0;
    cin >> inNum;
    if (inNum<0)
    {
        inNum = -inNum;
    }
    cout << inNum;

//16. 1보다 큰 수를 입력 받아, 1부터 그 수까지의 곱을 구하세요.  ( 3 --> 6 )

    int inNum = 0;
    cin >> inNum;
    int rt = 1;
    for (size_t i = 1; i <= inNum; i++)
    {
        rt *= i;
    }
    cout << rt;

//17. 총합, 평균 – 입력 받은 수들의 총합과 평균을 구해서 출력하세요. (while, 0 입력하면 종료)

    int total = 0;
    int count = 0;
    while (true)
    {
        int input = 0;
        cin >> input;
        if (input == 0) {
            break;
        }
        total += input;
        count++;
    }
    cout << total / (double)count;

//18. 최대, 최소 - 입력 받은 수들 중에서, 가장 큰 수 출력하기. (while, 0 입력하면 종료)

    int max = INT_MIN;
    while (true)
    {
        int input = 0;
        cin >> input;
        if (input == 0) {
            break;
        }

        if (input>max)
        {
            max = input;
        }
    }
    cout << max;

//19. 문자 - 입력 받은 문자가, 대문자 A ~ Z 중에 하나면 "대문자" 라고 출력하세요.

    char ch;
    cin >> ch;
    if ('A' <= ch && ch <= 'Z') {
        cout << "대문자";
    }

//20. 입력 받은 문자가, 대문자이면 소문자로, 소문자이면 대문자로 변경해서 출력하세요. ( A -> a, z -> Z )
    
    //char ch1 = 'a'; //97
    //char ch2 = 'A'; //65
    char ch;
    cin >> ch;
    if ('A' <= ch && ch <= 'Z') {
        ch=ch + ('a' - 'A');
    }
    else if ('a' <= ch && ch <= 'z')
    {
        ch = ch - ('a' - 'A');
    }
    else {
        ch = ch;
    }
    cout << ch;


//21. 정수를 입력하면, 각 자릿수의 숫자를 문자로 바꾸어 출력하세요. (123 -> 1, 2, 3)
    
    int input=0;
    cin >> input;
    int count = 0;
    char numsCh[10];

    while (true)
    {
        if (input == 0) {
            break;
        }
        numsCh[count] = input % 10+'0';
        input = input / 10;
        count++;
    }

    for (size_t i = count; i > 0; i--)
    {
        cout << numsCh[i-1];
        if (i - 1 != 0) {
            cout << ", ";
        }
    }

//22. 정수 N 을 입력하면, 약수 구하기.

    int input=0;
    cin >> input;

    for (size_t i = 1; i <= input; i++)
    {
        if (input % i == 0) {
            cout << i << " ";
        }
        else {
            continue;
        }
    }

//23. 정수 N 을 입력하면, 1 ~ N 사이의 소수 구하기.

    int input=0;
    cin >> input;

    for (size_t i = 1; i <= input; i++)
    {
        bool isPrime = true;
        for (size_t j = 2; j < i; j++)
        {
            if (i % j == 0) {
                isPrime = false;
            }
            else {
                continue;
            }
        }
        if (isPrime)
        {
            cout << i << " ";
        }
    }

//24. for문 이용하여 N 라인의 별 출력하기 (감소, 역순)

    ****
     ***
      **
       *

    int input=0;
    cin >> input;

    for (size_t i = 0; i < input; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            cout << " ";
        }
        for (size_t j = input-i; j > 0 ; j--)
        {
            cout << "*";
        }
        cout << '\n';
    }


//25. for문 이용하여 N 라인의 별 출력하기 (피라미드)

           *
          ***
         *****
        *******

    int input=0;
    cin >> input;

    for (size_t i = 0; i < input; i++)
    {
        for (size_t j = 0; j < input-i; j++)
        {
            cout << " ";
        }
        for (size_t j = 0; j < 2*i+1 ; j++)
        {
            cout << "*";
        }
        cout << '\n';
    }

*/