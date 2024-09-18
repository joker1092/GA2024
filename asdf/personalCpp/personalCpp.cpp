#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<int> getUniqueRandomNumbers(int count, int min, int max) {
    // 1부터 45까지의 숫자를 저장하는 벡터 생성
    std::vector<int> numbers;
    for (int i = min; i <= max; ++i) {
        numbers.push_back(i);
    }

    // 난수 생성기 설정
    std::random_device rd;  // 랜덤 시드
    std::mt19937 generator(rd()); // Mersenne Twister 엔진
    std::shuffle(numbers.begin(), numbers.end(), generator); // 숫자 섞기

    // 중복되지 않는 count 개수의 숫자 선택
    std::vector<int> result(numbers.begin(), numbers.begin() + count);
    return result;
}

int main() {
    int count = 6; // 추출할 숫자의 개수
    int min = 1;   // 최소 수치
    int max = 45;  // 최대 수치


    std::vector<std::vector<int>> lottos;

	for (int i = 0; i < 5; i++) {
		std::vector<int> randomNumbers = getUniqueRandomNumbers(count, min, max);
		std::sort(randomNumbers.begin(), randomNumbers.end());
		lottos.push_back(randomNumbers);
	}

    

    // 결과 출력
    std::cout << "랜덤 숫자: " << std::endl;
	for (auto nums : lottos) {
        for (int num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
	}
    
    return 0;
}
