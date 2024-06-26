#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


void printVector(const std::vector<int>& numbers)
{
    for (const auto& number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void PrintHint(std::vector<int>& numbers, int low, int high) {

    for (const auto& number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << low << " ";
    std::cout << high << " ";
    std::cout << std::endl;
}




void CountingSort(std::vector<int>& numbers)
{
    int max = *std::max_element(numbers.begin(), numbers.end()); //최대값
    int min = *std::min_element(numbers.begin(), numbers.end()); //최소값
    int range = max - min + 1; //최대 최소 사이의 겟수

    std::vector<int> count(range), output(numbers.size()); //range 겟수 만큼의 배열과 원본 크기 만큼의 배열을 만들어

    for (int i = 0; i < numbers.size(); i++)
    {
        count[numbers[i] - min]++; //range 배열에 해당하는 위치 값의 겟수를 센다
    }
    for (int i = 1; i < count.size(); i++)
    {
        count[i] += count[i - 1];  //최소 값에서 부터 최대값 까지 겟수를 누적
    }
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        output[count[numbers[i] - min] - 1] = numbers[i]; //출력 배열에 겟 수 센것 만큼 순번 대로 줄여가며 해당 하는 원본 배열의 값을 넣음
        count[numbers[i] - min]--;
    }
    for (int i = 0; i < numbers.size(); i++)
    {
        numbers[i] = output[i]; //출력배열 배출
    }
}


void MergeSort(std::vector<int>& numbers, int low, int high)
{
    PrintHint(numbers, low, high);

    if (low >= high) return;

    int mid = (low + high) / 2;
    MergeSort(numbers, low, mid);
    MergeSort(numbers, mid + 1, high);

    //Merge !!!
    std::vector<int> temp(numbers.size());
    int i = low;
    int j = mid + 1;
    int k = low;
    while (i <= mid && j <= high)
    {
        if (numbers[i] < numbers[j])
        {
            temp[k++] = numbers[i++];
        }
        else
        {
            temp[k++] = numbers[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = numbers[i++];
    }
    while (j <= high)
    {
        temp[k++] = numbers[j++];
    }
    for (int i = low; i <= high; i++)
    {
        numbers[i] = temp[i];
    }

    std::cout << "Merge : ";
    PrintHint(numbers, low, high);
}


int main()
{
    std::string input;
    std::vector<int> numbers;

    numbers.reserve(5);

    while (true)
    {
        std::getline(std::cin, input);

        std::istringstream iss(input);

        int number = 0;
        numbers.clear();

        while (iss >> number)
        {
            numbers.push_back(number);
        }

        std::cout << "capacity : " << numbers.capacity() << std::endl;
        std::cout << "size : " << numbers.size() << std::endl;

        if (0 == numbers.size()) break;

        printVector(numbers);

        MergeSort(numbers, 0, numbers.size() - 1);
        //std::cout << "count : " << InsertionSort(numbers) << std::endl;

        printVector(numbers);

    }

    return 0;
}