#pragma once
#include "framework.h"
#include "ReferenceCounter.h"

struct FRAME_INFO
{
    D2D1_RECT_F Source;
    D2D1_VECTOR_2F Center;
    float Duration;

    FRAME_INFO() {
        Source.left = 0;
        Source.top = 0;
        Source.right = 0;
        Source.bottom = 0;
        Center.x = 0;
        Center.y = 0;
        Duration = 0;
    }

    FRAME_INFO(float left, float top, float right, float bottom, float cx, float cy, float time ) {
        Source.left = left;
        Source.top = top;
        Source.right = right;
        Source.bottom = bottom;
        Center.x = cx;
        Center.y = cy;
        Duration = time;
    }

    FRAME_INFO(D2D1_RECT_F rect,float cx,float cy,float time) {
        Source = rect;
        Center.x = cx;
        Center.y = cy;
        Duration = time;
    }
};

struct MOTION
{
    std::string Name;
    std::vector<FRAME_INFO> Frames;
    bool Loop;
    MOTION() : Name("Default") { Frames.resize(10); }
};

class AnimationAsset :
    public ReferenceCounter
{
public:
    std::vector<MOTION> vMAnimations;

    AnimationAsset() { vMAnimations.resize(10); }
    virtual ~AnimationAsset() {};

    MOTION* GetMotionInfo(int index) {
        if (index < 0 && index > vMAnimations.size()) return nullptr;
        return &vMAnimations[index];
    }

    MOTION* GetMotionInfo(std::string MotionName) {
        for (auto& iter : vMAnimations )
        {
            if (iter.Name == MotionName)
            {
                return &iter;
            }
        }
        return nullptr;
    }

    bool LoadAnimation(std::wstring FilePath);
    bool LoadAnimationFromFile(int index, const wchar_t* filename);
};

