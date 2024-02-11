#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 FragPosView;
out vec3 NormalView;
out vec2 UV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat3 ViewModelRotation;

void main()
{
    vec4 fragmentPositionView = View * Model * vec4(aPos, 1.0);
    gl_Position = Projection * fragmentPositionView;

    FragPosView = vec3(fragmentPositionView);
    NormalView = normalize(ViewModelRotation * aNormal);
    UV = aUV;
}