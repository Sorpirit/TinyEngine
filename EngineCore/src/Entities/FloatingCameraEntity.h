#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "TinyEngineRT.h"
#include "Entity.h"
#include "Input.h"
#include "Render.h"
#include "FrameInfo.h"
#include "CameraSettings.h"

namespace EngineCore::Entities
{
    class FloatingCameraEntity : public Entity
    {
    public:
        void Init(const TinyEngineRT* engine) override;
        void Update(const FrameInfo& frameInfo) override;

        void SetTransform(const glm::mat4& transform) { _position = transform[3]; }
        void SetParameters(int screenWidth, int screenHeight, float fov);
    private:
        const Input* _input;
        EngineRender::Render* _render;

        CameraSettings _cameraSettings;
        
        glm::vec3 _position;

        glm::vec3 _rotationEurler;
        //TODO fix
        glm::quat _rotation;

        glm::vec3 _forward;
        glm::vec3 _up;
        
        
        float _speed = 19.5f;
        float _shiftSpeed = 50.0f;
    };
}
