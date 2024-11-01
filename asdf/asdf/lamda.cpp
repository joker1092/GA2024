//lamda_expressions

//lamda
//  �͸��Լ� (Anonymous function)
//  �Լ� �ڵ带 (���ٽ�)���� ǥ�� �Ͽ� ������ó�� ���
//  �ڵ��� ������, ������������ ���� ���� ���,���ʿ��� �ڵ� ����


//  [ĸ��](�Ű�����) -> ��ȯ�� {�Լ��ڵ�}

//��ȯ�� ���� ����  ==> [](){};

//[] : ĸ�ĸ���Ʈ, �ܺκ��� ����
//  - �ܺ� ������ ���ٽ� ���η� �������� ���
// [v] : value capture, v�� ������ ������,�� ����,���ٽ��� ����� ������ ĸ�ĵ� ������ ���� �����ؼ� ���ȭ
// [&v] : reference capture, v�� ������ ������,�� ����, c++ reference�� ����


//�Լ���ü�� lamda��
// �Լ� ��ü���� ���¿� ������ ������ �� �ִ� �ɹ������� ���� �� ������, ���ٽ��� �Ұ���
// ��, �Լ���ü�� ��ü�� �����ؾ� �Ѵٴ� ���� ����

//static binding
// [a,b] : a,b�� ������ ������ (����)
// ĸ�� ����� ���� ��������, ���� �ܺ� ������ ���� ����Ǿ ���ٽ� ������ ���� ������ ����
// �̶�  a,b�� closed over�� ������� ��

//���� ĸ�� ������ ����
// ���ٰ� ���� �� ���� ���� non-static ������ ĸ���� �� ����

//default capture
// [=] : ��� ������ ������ ������
// [&] : ��� ������ ������ ������



#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

//fucn
void func() {

}
//����!======================
auto incuruntLamdaFunc(int x) {
    return [&x]() { return x; }; // �Ű����� x�� ������ ������ //�Լ��� ������ ������ ������Ƿ� ����
}

template <typename Fn> //������ �����ϱ� ����Ƿ� ���� ���ָ� ����
void TempletFunc(Fn t) {
    t();
}


//main
int main(int arg) {
 
    //vector<int> v = { 0,1,2,3,4,5,6,7,8 };
    ////3�� ��� �� ���
    //
    //for_each(v.begin(), v.end(), [](int n) {if (n % 3 == 0&& n > 0) cout << n << " "; });

    //[v]() {for (auto& i : v) {
    //    if (i > 0 && i % 3 == 0) cout << i << " ";
    //    }
    //}(); //���ٽ��� �ٷ� ȣ��

    //cout << endl;

    //vector<int> vec1 = { 5,3,1,12,4,24,8 };
    //vector<int> vec2(7);
    ////vec1���� 2�� ���� vec2�� ����
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
    //cout << "Ȧ�� ���� ���� : " << count << endl;


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

