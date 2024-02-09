#include "Input.h"

namespace EngineCore
{
    Input* Input::instance_ = nullptr;
    
    Input::Input(GLFWwindow* window, int screenWidth, int screenHeight) : _window(window), _screenWidth(screenWidth), _screenHeight(screenHeight)
    {
        instance_ = this;
        
        glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            instance_->KeyCallback(key, scancode, action, mods);
        });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos)
        {
            instance_->MouseCallback(xpos, ypos);
        });

        glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            instance_->ScrollCallback(xoffset, yoffset);
        });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            instance_->MouseButtonCallback(button, action, mods);
        });

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        _mousePosition = glm::vec2(xpos, ypos);
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

    void Input::MouseButtonCallback(int button, int action, int mods)
    {
        if (button >= 0 && button < 8)
        {
            switch (action)
            {
            case GLFW_PRESS:
                _mouseButtons[button] = KeyState_Pressed;
                break;
            case GLFW_RELEASE:
                _mouseButtons[button] = KeyState_Released;
                break;
            }
        }
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

        for (auto& _button : _mouseButtons)
        {
            if (_button == KeyState_Pressed)
            {
                _button = KeyState_Held;
            }
            else if (_button == KeyState_Released)
            {
                _button = KeyState_None;
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

    bool Input::IsMouseButtonPressed(int button) const
    {
        return _mouseButtons[button] == KeyState_Pressed;
    }

    bool Input::IsMouseButtonHeld(int button) const
    {
        return _mouseButtons[button] == KeyState_Held;
    }

    bool Input::IsMouseButtonReleased(int button) const
    {
        return _mouseButtons[button] == KeyState_Released;
    }

    KeyState Input::GetMouseButtonState(int button) const
    {
        return _mouseButtons[button];
    }

    void Input::LockCursor(bool lock) const
    {
        if(lock)
        {
            //_mousePosition = glm::vec2(_screenWidth / 2, _screenHeight / 2);
            //glfwSetCursorPos(_window, _mousePosition.x, _mousePosition.y);
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}
