#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//template <typename T>
//void printArr(T* begin, T* end) {
//	T* it = begin;
//	while (it != end)
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//}
//=>
template <typename T>
void printVector(T begin, T end) {
	T it = begin;
	while (it != end)
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

template <typename T>
void printVectorV2(vector<T> v) {
	for (auto i : v)
	{
		cout << i << " ";
	}
	cout << endl;
}

template <typename T , typename U>
bool isValue(T begin, T end, U value) {
	T it = begin;
	while (it != end) {
		if(*it == value) {
			return true;
		}
		it++;
	}
	return false;
}

template <typename T>
void insertVector(vector<T>& v, T in) {
	auto it = v.begin();
	while (it != v.end()) {
		if (*it > in) {
			v.insert(it, in);
			return;
		}
		it++;
	}
	v.push_back(in);
}


int main() {

	vector<int> v2;

	insertVector(v2, 3);
	insertVector(v2, 1);
	insertVector(v2, 4);
	insertVector(v2, 2);

	printVector(v2.begin(), v2.end());

	return 0;
}