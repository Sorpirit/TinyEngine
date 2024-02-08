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
        
        _forward = glm::vec3(0, 0, -1.0f);
        _up = glm::vec3(0, 1.0f, 0);

        _cameraSettings.view = glm::lookAt(_position, _position + _forward, _up);
        _cameraSettings.projection = glm::perspective(glm::radians(90.0f), 1.0f, .05f, 100.0f);
        _cameraSettings.viewProjection = _cameraSettings.projection * _cameraSettings.view ;
        _render->SetMainCameraParams(_cameraSettings);
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
        
        auto mouseDelta = _input->GetScaledDeltaMousePosition();
        _rotationEurler.x += -mouseDelta.y * frameInfo.DeltaTime;
        _rotationEurler.y += -mouseDelta.x * frameInfo.DeltaTime;

        if(_rotation.x > glm::radians(89.0f))
            _rotationEurler.x = glm::radians(89.0f);
        if(_rotation.x < glm::radians(-89.0f))
            _rotationEurler.x = glm::radians(-89.0f);


        _rotation = glm::quat(_rotationEurler);
        _rotation = normalize(_rotation);
        auto rotationMatrix = mat3_cast(_rotation);
        
        /*_forward.x = cos(_rotationEurler.y) * cos(_rotationEurler.x);
        _forward.y = sin(_rotationEurler.x);
        _forward.z = sin(_rotationEurler.y) * cos(_rotationEurler.x);
        _forward = glm::normalize(_forward);*/

        _forward = rotationMatrix * glm::vec3(0, 0, 1.0f);
        _up = rotationMatrix * glm::vec3(0, 1.0f, 0);
        const auto right = rotationMatrix * glm::vec3(1.0f, 0.0f, 0);

        const float speed = _input->IsKeyHeld(GLFW_KEY_LEFT_SHIFT) ? _shiftSpeed : _speed;
        const float scaledSpeed = speed * frameInfo.DeltaTime;

        //translation
        
        if(_input->IsKeyHeld(GLFW_KEY_W))
            _position += _forward * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_S))
            _position += -_forward * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_D))
            _position += -right * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_A))
            _position += right * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_SPACE))
            _position += _up * scaledSpeed;

        if(_input->IsKeyHeld(GLFW_KEY_LEFT_CONTROL))
            _position += -_up * scaledSpeed;
        
        _cameraSettings.view = glm::lookAt(_position, _position + _forward, _up);
        _cameraSettings.viewProjection = _cameraSettings.projection * _cameraSettings.view;
        _render->SetMainCameraParams(_cameraSettings);
    }

    void FloatingCameraEntity::SetParameters(int screenWidth, int screenHeight, float fov)
    {
        const auto projection = glm::perspective(glm::radians(fov), static_cast<float>(screenWidth) / static_cast<float>(screenHeight), .05f, 100.0f);
        _cameraSettings.projection = projection;
    }
}
