
#version 330 core

#include<Lighting/PhongLighting.inc>

struct Material {
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

in vec3 FragPosView;
in vec3 NormalView;
in vec3 VertexColor;

uniform Material uMaterial;

out vec4 FragColor;

void main()
{
    vec3 result = vec3(0.0);

    result += PhongDirLight(FragPosView, NormalView, uMaterial.Diffuse, uMaterial.Specular, uMaterial.Shininess);
    result += PhongPointLight(FragPosView, NormalView, uMaterial.Diffuse, uMaterial.Specular, uMaterial.Shininess);
    result += PhongSpotLight(FragPosView, NormalView, uMaterial.Diffuse, uMaterial.Specular, uMaterial.Shininess);

    FragColor = vec4(result, 1.0);
} 