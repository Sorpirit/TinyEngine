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

out vec3 VertexColor;

void main()
{
    gl_Position = uCamera.Projection * uCamera.View * uModel * vec4(aPos, 1.0);

    VertexColor = aColor;
}