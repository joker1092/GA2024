#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;


void DoWork(unsigned id)
{
    std::cout << "Thread " << id << " is doing work\n";

    //std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main()
{
    int nConcurrency = std::thread::hardware_concurrency();

    cout << "hardware_concurrency : " << nConcurrency << endl;

    // thread 야 이 일좀 해줘 (worker 함수) -> (worker 객체)
    std::vector<std::thread> threads;

    constexpr unsigned int nThreads = 1;

    for (unsigned i = 0; i < nThreads; ++i)
    {
        threads.emplace_back(DoWork, i);
        //threads.back().detach();
    }

    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();

            std::cout << "Thread is joined\n";
        }
        else
        {
            std::cout << "Thread is not joinable\n";
        }
    }


    system("pause");
    return 0;
}