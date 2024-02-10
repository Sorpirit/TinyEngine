#pragma once

#include "glm/glm.hpp"

namespace EngineRender
{
    struct CameraSettings
    {
        glm::mat4 view;
        glm::mat4 projection;
    };
}
