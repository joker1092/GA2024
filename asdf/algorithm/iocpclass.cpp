#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

// 읽기 버퍼 크기
const int BUFFER_SIZE = 1024;

// 파일 관련 데이터 구조체
struct FileContext
{
    HANDLE fileHandle;                 // 파일 핸들
    OVERLAPPED overlapped;             // OVERLAPPED 구조체
    std::unique_ptr<char[]> buffer;    // 읽기 버퍼
    std::string fileName;              // 파일 이름
    DWORD bytesRead;                   // 읽은 바이트 수
};

// 에러 처리 함수
void HandleError(const char* msg)
{
    std::cerr << msg << " Error: " << GetLastError() << std::endl;
    exit(EXIT_FAILURE);
}

// 파일 읽기 작업 초기화
std::shared_ptr<FileContext> InitializeFileContext(const std::string& fileName, HANDLE iocp)
{
    auto context = std::make_shared<FileContext>();
    context->fileName = fileName;
    context->buffer = std::make_unique<char[]>(BUFFER_SIZE);

    // 파일 핸들 생성
    context->fileHandle = CreateFileA(
        fileName.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        nullptr
    );

    if (context->fileHandle == INVALID_HANDLE_VALUE)
    {
        HandleError(("Failed to open file: " + fileName).c_str());
    }

    // IOCP에 파일 핸들 연결
    if (CreateIoCompletionPort(context->fileHandle, iocp, reinterpret_cast<ULONG_PTR>(context.get()), 0) == nullptr)
    {
        HandleError("Failed to associate file with IOCP");
    }

    return context;
}

// IOCP 작업 처리 함수 (스레드에서 실행)
void IOCPWorker(HANDLE iocp, std::atomic<int>& activeFiles)
{
    DWORD bytesTransferred;
    ULONG_PTR completionKey;
    LPOVERLAPPED overlapped;

    while (activeFiles > 0)
    {
        if (GetQueuedCompletionStatus(iocp, &bytesTransferred, &completionKey, &overlapped, INFINITE))
        {
            auto* context = reinterpret_cast<FileContext*>(completionKey);

            if (overlapped ==nullptr)
            {
                std::cout << "Worker thread received exit signal." << std::endl;
                break;
            }

            // 읽기 완료 처리
            if (bytesTransferred > 0)
            {
                std::cout << "Read " << bytesTransferred << " bytes from " << context->fileName << ":\n";
                std::cout.write(context->buffer.get(), bytesTransferred);
                std::cout << "\n";

                          // 다음 읽기 요청
                context->overlapped.Offset += bytesTransferred;

                if (!ReadFile(context->fileHandle, context->buffer.get(), BUFFER_SIZE, nullptr, &context->overlapped)) {
                    if (GetLastError() != ERROR_IO_PENDING) {
                        HandleError(("Failed to read next chunk for file: " + context->fileName).c_str());
                    }
                }
            }
            else
            {
                // 파일 읽기 완료
                std::cout << "Finished reading " << context->fileName << "\n";

                // 파일 핸들 닫기
                CloseHandle(context->fileHandle);

                // 활성 파일 수 감소
                --activeFiles;
            }
        }
        else
        {
            HandleError("Failed to get completion status");
        }
    }

    std::cout << std::this_thread::get_id() << "Worker thread finished." << std::endl;
}

int main()
{
    // IOCP 생성
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
    if (iocp == nullptr)
    {
        HandleError("Failed to create IOCP");
        return 1;
    }

    // 읽을 파일 목록
    std::vector<std::string> files = { "example.txt", "example2.txt", "example3.txt" };
    std::vector<std::shared_ptr<FileContext>> fileContexts;

    // 활성 파일 카운터
    std::atomic<int> activeFiles(static_cast<int>(files.size()));

    // 파일 초기화 및 비동기 읽기 요청
    for (const auto& fileName : files)
    {
        auto context = InitializeFileContext(fileName, iocp);

        // OVERLAPPED 초기화
        ZeroMemory(&context->overlapped, sizeof(OVERLAPPED));
        context->bytesRead = 0;

        // 비동기 읽기 요청
        if (!ReadFile(context->fileHandle, context->buffer.get(), BUFFER_SIZE, nullptr, &context->overlapped))
        {
            if (GetLastError() != ERROR_IO_PENDING)
            {
                HandleError(("Failed to initiate read for file: " + fileName).c_str());
            }
        }

        fileContexts.push_back(context);
    }

    // 스레드 풀 생성
    const int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;

    for (int i = 0; i < numThreads; ++i)
    {
        workers.emplace_back(IOCPWorker, iocp, std::ref(activeFiles));
    }



    //모든 쓰레드를 종료시키고 받자
    for (int i = 0; i < numThreads; ++i) {
        PostQueuedCompletionStatus(iocp, 0, 0, nullptr);
    }
    

    // 모든 스레드가 종료될 때까지 대기
    for (auto& worker : workers)
    {
        worker.join();
    }

    // IOCP 핸들 닫기
    CloseHandle(iocp);

    std::cout << "All files processed." << std::endl;

    return 0;
}
