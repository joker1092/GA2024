#include <iostream>
#include <string>
using namespace std;

const char* acount = "1234-5678";
int  sid = 1122;
int balance = 1000;

class MyExeption
{
public:
    virtual void print() = 0;
};

class AcountExeption : public MyExeption
{
private:
    char* acc;
	int n;
public:
    AcountExeption(char* _acc,int _n) {
        acc = _acc;
		n = _n;
    }
	void print()
	{
		std::cout << "계좌번호 또는 비밀번호가 틀렸습니다." << endl;
        std::cout <<"입력 : 계좌 : " << acc <<"암호" << n << endl;
	}
};

class BalanceExeprion : public MyExeption
{
    int balance;
public:
    BalanceExeprion(int bal) {
		balance = bal;
	}
	void print()
	{
        std::cout << "잔액이 부족합니다." << endl;
        std::cout << "잔액 : " << balance << endl;
	}
};

int main()
{
    char acc[10];
    int id;
    int money;

    try {
        std::cout << "계좌번호 입력: "; cin >> acc;
        std::cout << "비밀번호 4자리 입력: "; cin >> id;
        if (strcmp(acount,acc)||sid!=id)
        {
            throw AcountExeption(acc,id);
        }


        std::cout << "출금액 입력 : "; cin >> money;
        if (balance < money)
        {
            throw BalanceExeprion(balance);
        }
        balance -= money;
        std::cout << "잔액 : " << balance << endl;
    }
    catch (AcountExeption ex)
	{
		ex.print();
	}
    catch (BalanceExeprion ex) {
        ex.print();
    }

    


    return 0;
}



