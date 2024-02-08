#pragma once

#include <glm/glm.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace EngineCore
{
    enum KeyState : unsigned char
    {
        KeyState_None,
        KeyState_Pressed,
        KeyState_Held,
        KeyState_Released,
    };

    class Input
    {
    public:
        Input(GLFWwindow* window);
        
        void KeyCallback(int key, int scancode, int action, int mode);
        void MouseCallback(double xpos, double ypos);
        void ScrollCallback(double xoffset, double yoffset);
        void ProcessInput();

        bool IsKeyPressed(int key) const;
        bool IsKeyHeld(int key) const;
        bool IsKeyReleased(int key) const;
        KeyState GetKeyState(int key) const;

        glm::vec2 GetMousePosition() const { return _mousePosition; }
        glm::vec2 GetDeltaMousePosition() const { return _deltaMousePosition; }
        glm::vec2 GetScaledDeltaMousePosition() const { return _deltaMousePosition * _sensitivity; }
        float GetSensitivity() const { return _sensitivity; }
        bool HasMouseMoved() const { return _hasMouseMoved; }

        float GetScrollOffset() const { return _scrollOffset; }

        void LockCursor(bool lock) const;
        
    private:
        GLFWwindow* _window;
        
        KeyState _keys[1024];

        bool _hasMouseMoved;
        glm::vec2 _mousePosition;
        glm::vec2 _deltaMousePosition;
        float _sensitivity = .35f;

        float _scrollOffset;

        static Input* instance_;
    };
}
