#include <iostream>
#include <array>



template <typename T, int size>
class MyArray {

	using reference = T&;

	private:
	T data[size];
	public:
	MyArray() {
		for (int i = 0; i < size; i++) {
			data[i] = T{};
		}
	}
	
	reference operator[](int index) {
		return data[index];
	}

	void print() {
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << " "; 
		}
		std::cout<<	std::endl;
	}
};


int main() {
	
	MyArray<int, 10> arr;

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;

	arr.print();

	return 0;
}