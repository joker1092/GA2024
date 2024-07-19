#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
	tuple<string, double, int> tp = make_tuple("abc", 3.154, 100);
	cout << get<0>(tp) << endl;
	cout << get<1>(tp) << endl;
	cout << get<2>(tp) << endl;
	return 0;
}