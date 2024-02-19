#version 330 core

#include<Lighting/PhongLighting.inc>

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    sampler2D Emissive;
    float Shininess;
};

in vec3 FragPosView;
in vec3 NormalView;
in vec2 UV;

uniform Material uMaterial;

uniform float uEmissiveStrength;

out vec4 FragColor;

void main()
{
    vec3 baseColor = texture(uMaterial.Diffuse, UV).rgb;
    vec3 specularColor = texture(uMaterial.Specular, UV).rgb;
    vec3 emissive = uEmissiveStrength * texture(uMaterial.Emissive, UV).rgb;

    vec3 result = vec3(0.0);

    result += PhongDirLight(FragPosView, NormalView, baseColor, specularColor, uMaterial.Shininess);
    result += PhongPointLight(FragPosView, NormalView, baseColor, specularColor, uMaterial.Shininess);
    result += PhongSpotLight(FragPosView, NormalView, baseColor, specularColor, uMaterial.Shininess);

    FragColor = vec4(result + emissive, 1.0);
} 