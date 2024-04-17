#pragma once
class TimeSystem
{
public:
    TimeSystem() = default;
    ~TimeSystem() = default;

    void InitTime();

    void UpdateTime();

    const float GetFrameRate();

    //const ULONGLONG GetDeltaTime();
    const float GetDeltaTime();

private:
    LARGE_INTEGER previousTime = { 0 };
    LARGE_INTEGER currentTime = { 0 };
    LARGE_INTEGER frequency = { 0 };
    float deltaTime = 0;
};

