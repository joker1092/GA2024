#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void func(int a) {
    for (size_t i = 0; i < 10; i++)
    {
        printf_s("func call");
    }
}//매개변수 있는 함수

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
    int sum = 0;
    for(auto itr= start; itr < end;++itr){
        sum += *itr;
    }
    *result = sum;
}


int main()
{
    //auto f1 = []() {
    //    printf_s("%d Hello world\n", std::this_thread::get_id());
    //    //std::cout << std::this_thread::get_id() << " " << "Hello world\n";
    //    std::this_thread::sleep_for(std::chrono::seconds(1));// 1초 대기
    //    };


    //thread t1(func,7); //매개변수 있는 함수 호출
    //thread t1([]() {func(7); });
    //t1.join();
    int datacount = 10000;
    int threadcount = 4;

    vector<int> data(10000);
    for (int i = 1; i <= 10000; i++) data[i - 1] = i;
    
    int sum = 0;

    vector<int> partial_sums(threadcount);
    vector<thread> threads(threadcount);

    for (int i = 0; i < threadcount; i++) {
        threads[i] = thread(worker, data.begin() + i * datacount / threadcount, data.begin() + (i + 1) * datacount / threadcount, &partial_sums[i]);
    }

    for (int i = 0; i < threadcount; i++) {
        threads[i].join();
        sum += partial_sums[i];
    }

    cout << "sum = " << sum << endl;


    std::cout << "메인 종료\n";

    return 0;
}