// 아래 벡터들의 합을 구하려고 합니다.
// 각각 별도 쓰레드로 벡터의 합을 구한 후,
// 메인에서는 그 합을 더해 출력하는 코드를 작성하세요. 

#include <iostream>
#include <vector>
#include <thread>
#include <future>
using namespace std;


int sum(vector<int>& v)
{
	int sum = 0;
	for (auto e : v) sum += e;
	return sum;
}


int main()
{
    vector<int> v1 = { 1,2,3 };
    vector<int> v2 = { 4,5,6 };
    vector<int> v3 = { 7,8,9 };      

	auto fut1 = async(sum,ref(v1));
	auto fut2 = async(sum, ref(v2));
	auto fut3 = async(sum, ref(v3));

	int sum = fut1.get() + fut2.get() + fut3.get();

	cout<< "sum: " << sum << endl;

}
