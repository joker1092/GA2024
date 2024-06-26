#pragma once
struct MouseState
{
    MouseState()
    {
        x = 0;
        y = 0;
        wheel = 0;
        left = false;
        right = false;
        middle = false;
    }

    int x;
    int y;
    int wheel;
    bool left;
    bool right;
    bool middle;
};

class InputSystem
{
public:
    

    void InitInput();

    void ResetInput();

    void KeyDown(unsigned int key);

    void KeyUp(unsigned int key);

    bool IsKeyDown(unsigned int key);

    bool IsKeyUp(unsigned int key);

    bool IsKey(unsigned int key);

    void UpdateMouse();

    bool IsSame(const MouseState& a, const MouseState& b);

    const MouseState& GetMouseState();
    const MouseState& GetPrevMouseState();
};

