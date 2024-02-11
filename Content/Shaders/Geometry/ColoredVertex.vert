#version 330 core

struct CameraSettings
{
    mat4 View;
    mat4 Projection;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

uniform CameraSettings uCamera;
uniform mat4 uModel;
uniform mat3 uViewModelRotation;

out vec3 FragPosView;
out vec3 NormalView;
out vec3 VertexColor;

void main()
{
    vec4 fragmentPositionView = uCamera.View * uModel * vec4(aPos, 1.0);
    gl_Position = uCamera.Projection * fragmentPositionView;

    FragPosView = vec3(fragmentPositionView);
    NormalView = normalize(uViewModelRotation * aNormal);
    VertexColor = aColor;
}