//SQLiteTestApp

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "sqlite3.h"
#include "sqlite_modern_cpp.h"

#ifdef _DEBUG
#pragma comment(lib, "sqlite3_d.lib")
#else
#pragma comment(lib, "sqlite3.lib")
#endif

std::string GetCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream ss;
    tm timeinfo;

    localtime_s(&timeinfo, &in_time_t);

    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");


    return ss.str();
}

// 로그를 기록하는 클래스
class Logger
{
private:
    sqlite::database db;

public:
    Logger(const std::string& db_path) : db(db_path)
    {
        // 로그 테이블 생성
        db << "CREATE TABLE IF NOT EXISTS Logs ("
            "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
            "Timestamp TEXT NOT NULL, "
            "LogLevel TEXT NOT NULL, "
            "Message TEXT NOT NULL"
            ");";
    }

    void Out(const std::string& level, const std::string& message)
    {
        std::string timestamp = GetCurrentTime();
        db << "INSERT INTO Logs (Timestamp, LogLevel, Message) VALUES (?, ?, ?);"
            << timestamp
            << level
            << message;

        // 로그를 콘솔에도 출력
        std::cout << "[" << timestamp << "] [" << level << "] " << message << std::endl;
    }

    void Query(const std::string& level = "")
    {
        if (level.empty()) {
            // 전체 로그 출력
            db << "SELECT Timestamp, LogLevel, Message FROM Logs;"
                >> [](std::string timestamp, std::string level, std::string message) {
                std::cout << "[" << timestamp << "] [" << level << "] " << message << std::endl;
                };
        }
        else {
            // 특정 레벨의 로그만 출력
            db << "SELECT Timestamp, LogLevel, Message FROM Logs WHERE LogLevel = ?;"
                << level
                >> [](std::string timestamp, std::string level, std::string message) {
                std::cout << "[" << timestamp << "] [" << level << "] " << message << std::endl;
                };
        }
    }
};

int main()
{
    try {
        // Logger 초기화
        Logger logger("logs.db");

        // 로그 기록
        logger.Out("INFO", "Application started.");
        logger.Out("DEBUG", "This is a debug message.");
        logger.Out("ERROR", "An error occurred.");
        logger.Out("INFO", "Application is running normally.");

        // 로그 조회
        std::cout << "\nAll Logs:" << std::endl;
        logger.Query();

        std::cout << "\nError Logs:" << std::endl;
        logger.Query("ERROR");

    }
    catch (const sqlite::sqlite_exception& e) {
        std::cerr << "SQLite Error: " << e.what() << std::endl;
    }

    return 0;
}
