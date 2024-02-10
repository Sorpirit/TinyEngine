#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 0) in vec3 aNormal;
layout (location = 1) in vec3 aColor;

out vec3 VertexColor;

uniform mat4 ViewProjection;

void main()
{
    gl_Position = ViewProjection * vec4(aPos, 1.0);

    VertexColor = aColor;
}