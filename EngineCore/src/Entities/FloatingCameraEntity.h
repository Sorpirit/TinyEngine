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
        void SetParameters(float fov, float near, float far);
    private:
        const Input* _input;
        EngineRender::Render* _render;

        CameraSettings _cameraSettings;
        
        glm::vec3 _position;

        glm::vec3 _rotationEurler;
        glm::quat _rotation;

        float _speed = 19.5f;
        float _shiftSpeed = 50.0f;
        float _rotationSpeed = 4.6f;
        float clampMouseDelta = 15.0f;
    };
}
