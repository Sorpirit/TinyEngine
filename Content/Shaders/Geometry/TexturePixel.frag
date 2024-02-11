#version 330 core

out vec4 FragColor;

in vec3 FragPosView;
in vec3 NormalView;
in vec2 UV;

uniform vec4 LightColor;
uniform vec3 LightPositionView;

uniform sampler2D colorTexture;

vec3 PhongLight(vec3 fragPos, vec3 nromal, vec3 lightPos, vec3 lightColor, float ambientStrength, float specularStrength, float shyness)
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - fragPos); 
    float diff = max(dot(nromal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, nromal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shyness);
    vec3 specular = specularStrength * spec * lightColor;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 light = vec3(0, 0, 0);
    light = PhongLight(FragPosView, NormalView, LightPositionView, LightColor.rgb, 0.1f, 0.5f, 32);

    vec4 baseColor = texture(colorTexture, UV);
    vec3 result = baseColor.rgb * light;
    FragColor = vec4(result, 1.0);
} 