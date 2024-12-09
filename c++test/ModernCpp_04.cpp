//아래 코드를 using 문을 사용해서 간략하게 변경하세요. 
//(별칭 템플릿으로 변경 )

#include <iostream>
#include <vector>

//template <typename T>
//struct MyVector {
//	typedef std::vector<T> type;	
//};

template <typename T>
using  MyVector = std::vector<T>;


int main()
{
	//MyVector<int>::type mv;        // ::type 
	MyVector<int> mv;        // using 사용

	mv.push_back(1);
	mv.push_back(2);
	mv.push_back(3);
	for (auto e : mv) std::cout << e << std::endl;

	return 0;
}
