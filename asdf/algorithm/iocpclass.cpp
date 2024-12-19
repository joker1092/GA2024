#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

// �б� ���� ũ��
const int BUFFER_SIZE = 1024;

// ���� ���� ������ ����ü
struct FileContext
{
    HANDLE fileHandle;                 // ���� �ڵ�
    OVERLAPPED overlapped;             // OVERLAPPED ����ü
    std::unique_ptr<char[]> buffer;    // �б� ����
    std::string fileName;              // ���� �̸�
    DWORD bytesRead;                   // ���� ����Ʈ ��
};

// ���� ó�� �Լ�
void HandleError(const char* msg)
{
    std::cerr << msg << " Error: " << GetLastError() << std::endl;
    exit(EXIT_FAILURE);
}

// ���� �б� �۾� �ʱ�ȭ
std::shared_ptr<FileContext> InitializeFileContext(const std::string& fileName, HANDLE iocp)
{
    auto context = std::make_shared<FileContext>();
    context->fileName = fileName;
    context->buffer = std::make_unique<char[]>(BUFFER_SIZE);

    // ���� �ڵ� ����
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

    // IOCP�� ���� �ڵ� ����
    if (CreateIoCompletionPort(context->fileHandle, iocp, reinterpret_cast<ULONG_PTR>(context.get()), 0) == nullptr)
    {
        HandleError("Failed to associate file with IOCP");
    }

    return context;
}

// IOCP �۾� ó�� �Լ� (�����忡�� ����)
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

            // �б� �Ϸ� ó��
            if (bytesTransferred > 0)
            {
                std::cout << "Read " << bytesTransferred << " bytes from " << context->fileName << ":\n";
                std::cout.write(context->buffer.get(), bytesTransferred);
                std::cout << "\n";

                          // ���� �б� ��û
                context->overlapped.Offset += bytesTransferred;

                if (!ReadFile(context->fileHandle, context->buffer.get(), BUFFER_SIZE, nullptr, &context->overlapped)) {
                    if (GetLastError() != ERROR_IO_PENDING) {
                        HandleError(("Failed to read next chunk for file: " + context->fileName).c_str());
                    }
                }
            }
            else
            {
                // ���� �б� �Ϸ�
                std::cout << "Finished reading " << context->fileName << "\n";

                // ���� �ڵ� �ݱ�
                CloseHandle(context->fileHandle);

                // Ȱ�� ���� �� ����
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
    // IOCP ����
    HANDLE iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
    if (iocp == nullptr)
    {
        HandleError("Failed to create IOCP");
        return 1;
    }

    // ���� ���� ���
    std::vector<std::string> files = { "example.txt", "example2.txt", "example3.txt" };
    std::vector<std::shared_ptr<FileContext>> fileContexts;

    // Ȱ�� ���� ī����
    std::atomic<int> activeFiles(static_cast<int>(files.size()));

    // ���� �ʱ�ȭ �� �񵿱� �б� ��û
    for (const auto& fileName : files)
    {
        auto context = InitializeFileContext(fileName, iocp);

        // OVERLAPPED �ʱ�ȭ
        ZeroMemory(&context->overlapped, sizeof(OVERLAPPED));
        context->bytesRead = 0;

        // �񵿱� �б� ��û
        if (!ReadFile(context->fileHandle, context->buffer.get(), BUFFER_SIZE, nullptr, &context->overlapped))
        {
            if (GetLastError() != ERROR_IO_PENDING)
            {
                HandleError(("Failed to initiate read for file: " + fileName).c_str());
            }
        }

        fileContexts.push_back(context);
    }

    // ������ Ǯ ����
    const int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;

    for (int i = 0; i < numThreads; ++i)
    {
        workers.emplace_back(IOCPWorker, iocp, std::ref(activeFiles));
    }



    //��� �����带 �����Ű�� ����
    for (int i = 0; i < numThreads; ++i) {
        PostQueuedCompletionStatus(iocp, 0, 0, nullptr);
    }
    

    // ��� �����尡 ����� ������ ���
    for (auto& worker : workers)
    {
        worker.join();
    }

    // IOCP �ڵ� �ݱ�
    CloseHandle(iocp);

    std::cout << "All files processed." << std::endl;

    return 0;
}
