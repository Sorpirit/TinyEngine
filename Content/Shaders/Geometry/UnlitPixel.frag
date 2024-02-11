#version 330 core

uniform vec3 uMultiplyColor;

in vec3 VertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(VertexColor * uMultiplyColor, 1.0);
} 