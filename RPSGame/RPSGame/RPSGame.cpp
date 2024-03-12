#include <iostream>
#include <Windows.h>

enum RPS {
	sscissors = 1,
	rock = 2,
	paper = 3,
};

int update() {
	
	Sleep(1000);
	system("cls");
	Sleep(1000);
	std::cout << "가위!바위!보!" << std::endl;
	std::cout << "숫자를 입력 해주세요." << std::endl;
	std::cout << "(1.가위,2.바위,3.보,4.종료)" << std::endl;

	int a;
	scanf_s("%d", &a);

	return a;
}
void rander(int set,int selected) {
	int a = selected;
	
	if (set == a) {
		std::cout << "비겼습니다" << std::endl;
	}
	else {
		if (set == 1 ) {
			if (a == 2) {
				std::cout << "이겼습니다" << std::endl;
			}
			else if (a == 3) {
				std::cout << "졌습니다." << std::endl;
			}
			else {
				std::cout <<"종료합니다" << std::endl;
			}
		}else if(set==2){
			if (a == 3) {
				std::cout << "이겼습니다" << std::endl;
			}
			else if (a == 1) {
				std::cout << "졌습니다." << std::endl;
			}
			else {
				std::cout << "종료합니다" << std::endl;
			}
		}
		else if (set == 3) {
			if (a == 1) {
				std::cout << "이겼습니다" << std::endl;
			}
			else if (a == 2) {
				std::cout << "졌습니다." << std::endl;
			}
			else {
				std::cout << "종료합니다" << std::endl;
			}
		}
		else {
			std::cout << "종료합니다" << std::endl;
		}
	}
	
}

int main()
{
	srand((unsigned int)time(nullptr));
	int set;
	int selected=0;
	while (selected!=4)
	{
		set = rand() % 2 + 1;
		selected = update();
		rander(set,selected);
	}
	return 0;
}
