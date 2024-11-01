#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

using namespace std;

std::queue<int> g_DummyQue;

std::mutex g_Mutex;

void DoWork()
{
    int nValue = 0;
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            if (false == g_DummyQue.empty())
            {
                nValue += g_DummyQue.front();
                g_DummyQue.pop();
            }
        }
    }
}


int main()
{
    int nConcurrency = std::thread::hardware_concurrency();

    cout << "hardware_concurrency : " << nConcurrency << endl;

    std::vector<std::thread> threads;

    constexpr unsigned int nThreads = 1;

    for (unsigned i = 0; i < nThreads; ++i)
    {
        threads.emplace_back(DoWork);
        threads.back().detach();
    }

    high_resolution_clock::time_point startTime = high_resolution_clock::now();

    unsigned int nIterations = 1000000;
    while (--nIterations > 0)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_DummyQue.push(nIterations);
    }

    high_resolution_clock::time_point endTime = high_resolution_clock::now();

    auto elapsedTime = duration_cast<duration<double, milli>>(endTime - startTime).count();
    cout << "Elapsed time : " << elapsedTime << "ms" << endl;

    system("pause");
    return 0;
}