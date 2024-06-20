#include <iostream>
#include <sstream>
#include <string>
#include <vector>


void printVector(const std::vector<int>& numbers)
{
    for (const auto& number : numbers)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}


void MySort(std::vector<int>& numbers)
{
    /*for (size_t i = 0; i < numbers.size()-1; i++)
    {
        for (size_t j = i+1; j < numbers.size(); j++)
        {
            if (numbers[i]>numbers[j])
            {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }*/

    /*for (size_t i = 0; i < numbers.size() - 1; i++)
    {
        int small = numbers[i];
        int index = i;
        for (size_t j = i; j < numbers.size() ; j++)
        {
            if (small > numbers[j]) {
                small = numbers[j];
                index = j;
            }
        }
        int temp = numbers[i];
        numbers[i] = small;
        numbers[index] = temp;
    }*/

    for (size_t i = 0; i < numbers.size(); i++)
    {
        int count = 0;
        for (size_t j = 0; j < numbers.size() - 1 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                count++;
            }
        }
        if (count == 0) break;
    }
}

int BubbleSort(std::vector<int>& numbers)
{
    int loof = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        int count = 0;
        for (int j = 0; j < numbers.size() - 1 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                std::swap(numbers[j], numbers[j + 1]);
                count++;
                loof++;
            }
        }
        if (count == 0) break;
    }

    return loof;
}

int SelectSort(std::vector<int>& numbers)
{
    int count = 0;
    //int loof = 0;
    for (size_t i = 0; i < numbers.size() - 1; i++)
    {
        int index = i;
        for (size_t j = i + 1; j < numbers.size(); j++)
        {
            if (numbers[i] > numbers[j]) {
                index = j;
            }
            //loof++;
        }
        if (i != index) {
            int temp = numbers[i];
            numbers[i] = numbers[index];
            numbers[index] = temp;
            count++;
        }
    }

    return count;
}
int InsertionSort(std::vector<int>& numbers) {
    int count = 0;
    for (size_t i = 1; i < numbers.size(); i++) {
        for (size_t j = i; j > 0; j--)
        {
            if (numbers[j] < numbers[j - 1])
            {
                std::swap(numbers[j], numbers[j - 1]);
                count++;
            }
            else {
                break;
            }
        }
    }

    return count;
}

int partition(std::vector<int>& numbers, int low, int high) {
    int pivot = numbers[high];

    int i = (low - 1);

    for (size_t j = low; j <= high; j++)
    {
        //todo
        if (numbers[j] < pivot) {
            //i = j + 1;
            i++;
            std::swap(numbers[i], numbers[j]);
        }
    }
    std::swap(numbers[i + 1], numbers[high]);
    printVector(numbers);
    return (i + 1);
}

void QuickSort(std::vector<int>& numbers, int low, int high) {

    if (low > high) return;
    int pi = partition(numbers, low, high);

    QuickSort(numbers, low, pi - 1);
    QuickSort(numbers, pi + 1, high);
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

        QuickSort(numbers, 0, numbers.size() - 1);
        //std::cout << "count : " << InsertionSort(numbers) << std::endl;

        printVector(numbers);

    }

    return 0;
}