#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


int main() {

	int level;

	level = 20;
	[](int level) {
		if (level > 10)
		{
			cout << "ok" << endl;
		}
		else {
			cout << "fail" << endl;
		}
	}(level);

	int number;
	cin >> number;
	[number](){
		if(number>10)
		cout<<number<<endl;
		}();

	function<int(int)> func = [](int a) -> int {return a + 1; };
	cout << func(1) << endl; //2;

	vector<int> v = { 0,1,2,3,4,5,6,7,8 };
	for_each(v.begin(), v.end(), [](int a) {if (a % 3 == 0)cout << a << endl; });

	vector<int> vec1 = { 5,3,1,12,4,24,8 };
	vector<int> vec2(7);
	transform(vec1.begin(), vec1.end(), vec2.begin(), [](int a) {return a * 2; });

	vector<int> vec{ 5,3,1,2,3,4 };
	int count = 0;
			
	vec.erase(remove_if(vec.begin(), vec.end(), [&count](int a) {if (a % 2 != 0) { count++; return true; } else return false; }));
	cout<< count << endl;
		
	
	return 0;
}