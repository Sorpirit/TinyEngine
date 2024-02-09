#include "FloatingCameraEntity.h"

#include "Math/MatrixHelpers.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace EngineCore::Entities
{
    void FloatingCameraEntity::Init(const TinyEngineRT* engine)
    {
        _input = engine->GetInput();
        _render = engine->GetRender();

        _position = glm::vec3(0, 0, 1.0f);
        _rotationEurler = glm::vec3(0, glm::radians(-90.0f), 0);
        _rotation = glm::quat(_rotationEurler);
        
        const glm::vec3 forward = glm::vec3(0, 0, -1.0f);
        const glm::vec3 up = glm::vec3(0, 1.0f, 0);

        _cameraSettings.view = glm::lookAt(_position, _position + forward, up);
        _cameraSettings.projection = glm::perspective(glm::radians(90.0f), 1.0f, .05f, 100.0f);
        _render->SetMainCameraParams(_cameraSettings);

        _input->LockCursor(true);
    }

    void FloatingCameraEntity::Update(const FrameInfo& frameInfo)
    {
        //rotation
        const float sensitivity = _input->GetSensitivity(); 
        if(_input->IsKeyHeld(GLFW_KEY_Q))
            _rotationEurler.z += sensitivity * frameInfo.DeltaTime;

        if(_input->IsKeyHeld(GLFW_KEY_E))
            _rotationEurler.z -= sensitivity * frameInfo.DeltaTime;

        if(_input->IsKeyReleased(GLFW_KEY_ESCAPE))
            _input->LockCursor(false);

        if (_input->IsMouseButtonPressed(0))
            _input->LockCursor(true);
        
        auto mouseDelta = _input->GetScaledDeltaMousePosition();
        _rotationEurler.x += glm::clamp(mouseDelta.y, -clampMouseDelta, clampMouseDelta) * _rotationSpeed * frameInfo.DeltaTime;
        _rotationEurler.y += -glm::clamp(mouseDelta.x, -clampMouseDelta, clampMouseDelta) * _rotationSpeed * frameInfo.DeltaTime;

        _rotationEurler.x = glm::clamp(_rotationEurler.x, -75.0f, 75.0f);
        _rotation = glm::quat(_rotationEurler);
        _rotation = normalize(_rotation);
       
        //translation

        const glm::vec3 forward = _rotation * glm::vec3(0, 0, -1.0f);
        const glm::vec3 up = _rotation * glm::vec3(0, 1.0f, 0);
        const glm::vec3 right = _rotation * glm::vec3(1.0f, 0.0f, 0);

        const float speed = _input->IsKeyHeld(GLFW_KEY_LEFT_SHIFT) ? _shiftSpeed : _speed;
        const float scaledSpeed = speed * frameInfo.DeltaTime;

        if(_input->IsKeyHeld(GLFW_KEY_W))
            _position += forward * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_S))
            _position += -forward * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_D))
            _position += right * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_A))
            _position += -right * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_SPACE))
            _position += up * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_LEFT_CONTROL))
            _position += -up * scaledSpeed;
        
        _cameraSettings.view = glm::lookAt(_position, _position + forward, up);
        _render->SetMainCameraParams(_cameraSettings);
    }

    void FloatingCameraEntity::SetParameters(float fov, float near, float far)
    {
        const auto projection = glm::perspective(glm::radians(fov), static_cast<float>(_render->GetScreenWidth()) / static_cast<float>(_render->GetScreenHeight()), near, far);
        _cameraSettings.projection = projection;
    }
}
