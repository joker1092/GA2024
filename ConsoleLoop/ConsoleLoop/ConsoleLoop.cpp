#include <iostream>

#include <winnt.h>
#include <ktmtypes.h>
#include <minwinbase.h>
#include <sysinfoapi.h>

namespace global
{
    namespace time {
        ULONGLONG previousTime;
        ULONGLONG currentTime;
        ULONGLONG deltaTime;

        int updateCount;
        int fixedUpdateCount;

        void InitTime() {
            previousTime = currentTime = GetTickCount64();
        }

        void UpdateTime() {
            previousTime = currentTime;
            currentTime = GetTickCount64();
            deltaTime = currentTime - previousTime;
        }

        ULONGLONG GetDeltaTime() {
            return deltaTime;
        }
    }
}

void StartGame() {

}

void EndGame() {

}

void ProcessInput() {

}

void FixedUpdate() {

}

void Update() {

}

void Render() {

}

bool IsGameRun() {

}

void PrintPerSecond() {
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();
    if (elapsedTime >= 1000)
    {
        printf("updateCount : %d \t fixedUpdateCount : d \n", global::time::updateCount, global::time::fixedUpdateCount);

        elapsedTime = 0;
        global::time::updateCount = 0;
        global::time::fixedUpdateCount = 0;
    }
}

int main()
{
    global::time::InitTime();

    StartGame();

    while (IsGameRun) {
        global::time::UpdateTime();

        ProcessInput();

        FixedUpdate();

        Update();

        PrintPerSecond();
    }

    EndGame();

    return 0;
}


