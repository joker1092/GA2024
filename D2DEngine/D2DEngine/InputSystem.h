#pragma once
#include "framework.h"
class InputSystem
{
public:
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
    void InitInput(HWND _hwnd, int screenX, int screenY);
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

    void AddBuffer(TCHAR _buffer);
    void SetInputState(bool on);
    int GetInputBuffer(TCHAR* in, int count, int maxLength);
private:
    bool isKeyDown[256];
    bool isKeyUp[256];
    bool isKey[256];

    MouseState curMouse;
    MouseState prevMouse;

    TCHAR buffer[255] = { 0 };
    int length = 0;
    bool isInputKey = false;

    HWND hwnd;
    int screenWidth;
    int screenHeight;

    void InitMouse()
    {
        curMouse.x = screenWidth / 2;
        curMouse.y = screenHeight / 2;
        curMouse.wheel = 0;

        curMouse.left = false;
        curMouse.right = false;
        curMouse.middle = false;

        prevMouse = curMouse;

        SetCursorPos(curMouse.x, curMouse.y);
    }
};

