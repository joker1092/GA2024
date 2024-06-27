#include "TimeSystem.h"

void TimeSystem::InitTime()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&previousTime);
}

void TimeSystem::UpdateTime()
{
    QueryPerformanceCounter(&currentTime);

    deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (frequency.QuadPart / 1000.f)/1000.f;
    previousTime = currentTime;
}

void TimeSystem::SetTimeScale(float _timeScale)
{
    timeScale = _timeScale;
}

const float TimeSystem::GetFrameRate()
{
    if (deltaTime == 0) return 0;
    return ceil(((1000.0f / deltaTime) * 1000) / 1000);
}

const float TimeSystem::GetDeltaTime()
{
    return deltaTime * timeScale;
}

const float TimeSystem::GetUnscaleDeltaTime()
{
    return deltaTime;
}

const float TimeSystem::GetTimeScale()
{
    return timeScale;
}
