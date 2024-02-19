struct DirectionalLight {
    vec3 DirectionView;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
    vec3 PositionView;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight {
    vec3 PositionView;
    vec3 DirectionView;
    float OuterConeAngleCos;
    float InnerConeAngleCos;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

uniform DirectionalLight uDirLight;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;

vec3 PhongDirLight(vec3 fragPos, vec3 nromal, vec3 baseColor, vec3 specularColor, float shininess)
{
    vec3 ambient = baseColor * uDirLight.Ambient;
    
    vec3 lightDir = normalize(-uDirLight.DirectionView); 
    float diff = max(dot(nromal, lightDir), 0.0);
    vec3 diffuse = diff * baseColor * uDirLight.Diffuse;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, nromal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * specularColor * uDirLight.Specular;

    return (ambient + diffuse + specular);
}

vec3 PhongPointLight(vec3 fragPos, vec3 nromal, vec3 baseColor, vec3 specularColor, float shininess)
{
    vec3 ambient = baseColor * uPointLight.Ambient;

    vec3 toLight = uPointLight.PositionView - fragPos; 
    float distance = length(toLight);
    float attenuation = 1.0f / (uPointLight.Constant + uPointLight.Linear * distance + uPointLight.Quadratic * distance * distance);

    vec3 lightDir = normalize(uPointLight.PositionView - fragPos); 
    float diff = max(dot(nromal, lightDir), 0.0);
    vec3 diffuse = diff * baseColor * uPointLight.Diffuse;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, nromal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * specularColor * uPointLight.Specular;

    return (ambient + diffuse + specular) * attenuation;
}

vec3 PhongSpotLight(vec3 fragPos, vec3 nromal, vec3 baseColor, vec3 specularColor, float shininess)
{
    vec3 ambient = baseColor * uSpotLight.Ambient;

    vec3 toLight = uSpotLight.PositionView - fragPos; 
    float distance = length(toLight);
    float attenuation = 1.0f / (uSpotLight.Constant + uSpotLight.Linear * distance + uSpotLight.Quadratic * distance * distance);

    vec3 lightDir = normalize(uSpotLight.PositionView - fragPos); 

    float theta = dot(-lightDir, normalize(uSpotLight.DirectionView));

    float epsilon = uSpotLight.InnerConeAngleCos - uSpotLight.OuterConeAngleCos;
    float intensity = smoothstep(0.0, 1.0, (theta - uSpotLight.OuterConeAngleCos) / epsilon);

    float diff = max(dot(nromal, lightDir), 0.0);
    vec3 diffuse = intensity * diff * baseColor * uSpotLight.Diffuse;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, nromal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = intensity * spec * specularColor * uSpotLight.Specular;

    return (ambient + diffuse + specular) * attenuation;
}
