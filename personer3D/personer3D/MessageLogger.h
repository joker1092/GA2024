#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <string>
#include <chrono>

class MessageLogger {
public:
    MessageLogger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file: "+ filename);
        }
        worker = std::thread(&MessageLogger::workerThread, this);
    }

    ~MessageLogger() {
        // 쓰레드 종료를 위한 신호 (예: 큐에 특별한 값을 넣거나, 조건 변수를 이용)
        {
            std::lock_guard<std::mutex> lock(mtx);
            messageQueue.push("exit");
        }
        cv.notify_one();
        worker.join();
    }

    void logMessage(const std::string& message) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            messageQueue.push(message);
        }
        cv.notify_one();
    }

private:
    void workerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !messageQueue.empty(); });

            std::string message = messageQueue.front();
            messageQueue.pop();
            lock.unlock();

            if (message == "exit") {
                break;
            }

            auto now = std::chrono::system_clock::now();
            std::string timestamp = std::format("{:%Y / %m / %d  %H : %M : %S}",std::chrono::floor<std::chrono::milliseconds>(now));
            timestamp.pop_back();

            logFile << timestamp << " => msg : " << message << std::endl;
        }
    }
private:
    std::ofstream logFile;
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::string> messageQueue;
    std::thread worker;
};
