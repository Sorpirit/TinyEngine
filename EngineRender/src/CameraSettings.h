#pragma once

#include "glm/glm.hpp"

#include "ParameterBuilder.h"

namespace EngineRender
{
    struct CameraSettings : public ShaderData
    {
        glm::mat4 View;
        glm::mat4 Projection;

        void UploadData(ParameterBuilder& builder) const override {
            builder.AddParameter("uCamera.View", View);
            builder.AddParameter("uCamera.Projection", Projection);
        }
    };
}
