#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>

using namespace std;

//int main() {

    //mutex
    //int shared_memory = 0;

    //mutex mtex;


    //auto count_func = [&]() {
    //    for (int i = 0; i < 100000; ++i) {
    //        mtex.lock();
    //        shared_memory++;
    //        mtex.unlock();
    //    }
    //};


    //thread t1(count_func);
    //thread t2(count_func);

    //t1.join();
    //t2.join();

    //cout<< "after count : " << shared_memory << endl;  //non mutex : 118000~ 160000 -> mutex : 200000

    
    //atomic


    //int shared_memory = 0;
    //mutex mtex;

    //auto count_func = [&]() {
    //    std::lock_guard < std::mutex > lock(mtex);
    //    for (int i = 0; i < 100000; ++i) {

    //        shared_memory++;
    //    }
    //};


    //thread t1(count_func);
    //thread t2(count_func);

    //t1.join();
    //t2.join();

    //cout << "after count : " << shared_memory << endl;  //non mutex : 118000~ 160000 -> mutex : 200000

//}

//std::mutex mtx;
//std::condition_variable cv;
//
//bool ready1 = false;
//bool ready2 = false;
//int nums = 0;
//
//void worker_thread1() {
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::unique_lock<std::mutex> lck(mtx);
//
//    cv.wait(lck, [] {return ready1; });
//
//    printf("worker Thread1\n");
//    nums++;
//}
//
//void worker_thread2() {
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::unique_lock<std::mutex> lck(mtx);
//
//    cv.wait(lck, [] {return ready2; });
//
//    printf("worker Thread2\n");
//    nums++;
//}
//
//
//int main() {
//    
//    std::thread t1 (worker_thread1);
//    std::thread t2 (worker_thread2);
//
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//
//    ready1 = true;
//    ready2 = true;
//
//    cv.notify_all();
//
//    t1.join();
//    t2.join();
//
//}

std::mutex mtx;
std::condition_variable cv;
std::queue<int> q;


void product(int n) {
    {
        std::unique_lock<std::mutex> lck(mtx);
        q.push(n);
    }
    cv.notify_one();
}


void cunsum() {

    std::unique_lock<std::mutex> lck(mtx);    
    if (q.empty())
    {
        cv.wait(lck, [] {return !q.empty(); });
    }
    int val = q.front();
    cout<< "cunsum : " << val << endl;
    q.pop();
}

int MEX_INT = 200;

int main() {
    std::vector<std::thread> productions;
    std::vector<std::thread> cunsumers;
    
    for (int i = 0; i < MEX_INT; i++) {
        productions.push_back(std::thread(product, i+1));
    }

    for (int i = 0; i < MEX_INT; i++) {
        cunsumers.push_back(std::thread(cunsum));
    }

    for (size_t i = 0; i < MEX_INT; i++)
    {
        productions[i].join();
    }

    cv.notify_all();
    
    for (size_t i = 0; i < MEX_INT; i++)
    {
        cunsumers[i].join();
    }
    
}
