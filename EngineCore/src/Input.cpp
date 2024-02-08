#include "Input.h"

namespace EngineCore
{
    Input* Input::instance_ = nullptr;
    
    Input::Input(GLFWwindow* window)
    {
        instance_ = this;

        _window = window;
        
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            instance_->KeyCallback(key, scancode, action, mods);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
        {
            instance_->MouseCallback(xpos, ypos);
        });

        glfwSetCursorPos(window, 1024 / 2, 768 / 2);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Input::KeyCallback(int key, int scancode, int action, int mode)
    {
        if (key >= 0 && key < 1024)
        {
            switch (action)
            {
            case GLFW_PRESS:
                _keys[key] = KeyState_Pressed;
                break;
            case GLFW_RELEASE:
                _keys[key] = KeyState_Released;
                break;
            }
        }
    }

    void Input::MouseCallback(double xpos, double ypos)
    {
        auto newMousePosition = glm::vec2(xpos, ypos);
        _deltaMousePosition.x = newMousePosition.x - _mousePosition.x;
        _deltaMousePosition.y = _mousePosition.y - newMousePosition.y;
        _mousePosition = newMousePosition;
        _hasMouseMoved = true;
    }

    void Input::ScrollCallback(double xoffset, double yoffset)
    {
        _scrollOffset = yoffset;
    }

    void Input::ProcessInput()
    {
        for (auto& _key : _keys)
        {
            if (_key == KeyState_Pressed)
            {
                _key = KeyState_Held;
            }
            else if (_key == KeyState_Released)
            {
                _key = KeyState_None;
            }
        }

        _hasMouseMoved = false;
        _deltaMousePosition = glm::vec2(0.0f);
        _scrollOffset = 0.0f;
    }

    bool Input::IsKeyPressed(int key) const
    {
        return _keys[key] == KeyState_Pressed;
    }

    bool Input::IsKeyHeld(int key) const
    {
        return _keys[key] == KeyState_Held;
    }

    bool Input::IsKeyReleased(int key) const
    {
        return _keys[key] == KeyState_Released;
    }

    KeyState Input::GetKeyState(int key) const
    {
        return _keys[key];
    }

    void Input::LockCursor(bool lock) const
    {
        if(lock)
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}
