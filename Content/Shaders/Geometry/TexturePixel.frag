#version 330 core

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct Light {
    vec3 PositionView;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

in vec3 FragPosView;
in vec3 NormalView;
in vec2 UV;

uniform Light uLight;
uniform Material uMaterial;

uniform sampler2D uColorTexture;

out vec4 FragColor;

vec3 PhongLight(vec3 fragPos, vec3 nromal)
{
    vec3 ambient = uMaterial.Ambient * uLight.Ambient;

    vec3 lightDir = normalize(uLight.PositionView - fragPos); 
    float diff = max(dot(nromal, lightDir), 0.0);
    vec3 diffuse = diff * uMaterial.Diffuse * uLight.Diffuse;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, nromal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.Shininess);
    vec3 specular = spec * uMaterial.Specular * uLight.Specular;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 light = PhongLight(FragPosView, NormalView);

    vec4 baseColor = texture(uColorTexture, UV);
    vec3 result = baseColor.rgb * light;
    FragColor = vec4(result, 1.0);
} 