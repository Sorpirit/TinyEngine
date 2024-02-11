#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 FragPosView;
out vec3 NormalView;
out vec3 VertexColor;

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
    VertexColor = aColor;
}