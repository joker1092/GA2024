//lamda_expressions

//lamda
//  익명함수 (Anonymous function)
//  함수 코드를 (람다식)으로 표현 하여 데이터처럼 사용
//  코드의 간결함, 지연연산으로 인한 성능 향상,불필요한 코드 제거


//  [캡쳐](매개변수) -> 반환형 {함수코드}

//반환형 생략 가능  ==> [](){};

//[] : 캡쳐리스트, 외부변수 참조
//  - 외부 변수를 람다식 내부로 가져오는 방법
// [v] : value capture, v를 값으로 가져옴,값 복사,람다식이 선언된 시점의 캡쳐된 변수의 값을 복사해서 상수화
// [&v] : reference capture, v를 참조로 가져옴,값 참조, c++ reference와 동일


//함수객체와 lamda식
// 함수 객체에는 상태와 변수를 저장할 수 있는 맴버변수를 가질 수 있지만, 람다식은 불가능
// 단, 함수객체는 객체를 생성해야 한다는 점이 단점

//static binding
// [a,b] : a,b를 값으로 가져옴 (복사)
// 캡쳐 당시의 값을 가져오며, 이후 외부 변수의 값이 변경되어도 람다식 내부의 값은 변하지 않음
// 이때  a,b는 closed over된 변수라고 함

//람다 캡쳐 변수의 범위
// 람다가 선언 된 범위 내에 non-static 변수를 캡쳐할 수 있음

//default capture
// [=] : 모든 변수를 값으로 가져옴
// [&] : 모든 변수를 참조로 가져옴



#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

//fucn
void func() {

}
//주의!======================
auto incuruntLamdaFunc(int x) {
    return [&x]() { return x; }; // 매개변수 x를 참조로 가져옴 //함수가 끝나면 참조가 사라지므로 주의
}

template <typename Fn> //형식을 구분하기 힘들므로 변경 해주면 좋다
void TempletFunc(Fn t) {
    t();
}


//main
int main(int arg) {
 
    //vector<int> v = { 0,1,2,3,4,5,6,7,8 };
    ////3의 배수 만 출력
    //
    //for_each(v.begin(), v.end(), [](int n) {if (n % 3 == 0&& n > 0) cout << n << " "; });

    //[v]() {for (auto& i : v) {
    //    if (i > 0 && i % 3 == 0) cout << i << " ";
    //    }
    //}(); //람다식을 바로 호출

    //cout << endl;

    //vector<int> vec1 = { 5,3,1,12,4,24,8 };
    //vector<int> vec2(7);
    ////vec1에서 2배 값을 vec2에 저장
    ////transform(vec1.begin(), vec1.end(), vec2.begin(), [](int n) {return n * 2; });

    //[&vec1, &vec2]() {
    //    for (int i = 0; i < vec1.size(); i++) {
    //        vec2[i] = vec1[i] * 2;
    //    }
    //    }();

    //for (auto i : vec1)
    //{
    //    cout << i << " ";
    //}

    //cout<< endl;

    //for (auto i : vec2) {
    //    cout << i << " ";
    //}

    //cout << endl;


    //std::vector<int> vec{ 5,3,1,2,3,4 };
    //int count = 0;
    //vec.erase(remove_if(vec.begin(), vec.end(), [&count](int n) {if (n % 2 != 0) { count++; return true; }else return false; }));
    //cout << "홀수 지운 개수 : " << count << endl;


    // std::string str = "hello";
   
    // auto stringUpper = [](std::string& str) {for (auto& c : str) c = toupper(c); };

    // cout<< str << endl;
    // 
    // auto stringfn = [](std::string& str, function<void(std::string&)> fn)->std::string {fn(str); return str; };

    // cout << stringfn(str, stringUpper) << endl;

    auto plus3 = [](int x) {return x + 3; };

    auto plus = [](int t) -> auto {return [t](int x) {return x + t; }; };

    auto plus5 = plus(5);

    cout << plus5(10) << endl;

    //++
    auto increase = [](int x) {return x++; };
    //*
    auto mul = [](int t) -> auto {return [t](int x) {return x * t; }; };
    //-
    auto sub = [](int t) -> auto {return [t](int x) {return x - t; }; };

    //2*3+1
    cout << increase(mul(2)(3)) << endl;

    //1++*2++
    cout << mul(increase(1))(increase(2)) << endl;

    return 0;
}

