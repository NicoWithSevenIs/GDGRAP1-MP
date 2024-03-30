#version 330 core

out vec4 FragColor;

uniform sampler2D tex0;

uniform vec3 pointLightPos;
uniform vec3 pointLightColor;

uniform float pointLightAmbientStr; 
uniform vec3  pointLightAmbientColor;

uniform float pointLightSpecStr;
uniform float pointLightSpecPhong;

uniform float constant;
uniform float linear;
uniform float quadratic;

uniform vec3 directionLightDir;

uniform vec3 directionLightColor;

uniform float directionLightAmbientStr; 
uniform vec3  directionLightAmbientColor;

uniform float directionLightSpecStr;
uniform float directionLightSpecPhong;

uniform vec3 cameraPos;

uniform float directionLightBrightness;

uniform float pointLightBrightness;


in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

in mat3 TBN;

void main() {
    
    vec3 normal = normalize(normCoord);
    
    vec3 viewDir = normalize(cameraPos - fragPos);

    // POINT LIGHT STUFF //

    vec3 lightDir = normalize(pointLightPos - fragPos);
    float diff =  max(dot(normal, lightDir), 0.0);

    vec3 diffuse = diff * pointLightColor;
    
    vec3 ambientCol = pointLightAmbientColor * pointLightAmbientStr;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.1), pointLightSpecPhong);
    
    vec3 specColor = spec * pointLightSpecStr * pointLightColor;

    float distance = length(pointLightPos - fragPos);

    float attentuation_denominator = constant + (linear * distance) + (quadratic * (distance * distance));
    float attentuation = 1.0f / attentuation_denominator;

    specColor *= attentuation;
    diffuse *= attentuation;
    ambientCol *= attentuation;
    
    vec3 pointLightResult = (specColor + diffuse + ambientCol) * pointLightBrightness;

    // DIRECTIONAL LIGHT //

    vec3 lightDir2 = normalize(-directionLightDir);
    float diff2 = max(dot(normal, lightDir2), 0.0);
    vec3 diffuse2 = diff2 * directionLightColor;
    vec3 ambientCol2 = directionLightColor * directionLightAmbientStr;
    vec3 reflectDir2 = reflect(-lightDir2, normal);
    float spec2 = pow(max(dot(reflectDir2, viewDir), 0.1), directionLightSpecPhong);
    vec3 specColor2 = spec2 * directionLightSpecStr * directionLightColor;
    
    vec3 dirLightResult = (specColor2 + diffuse2 + ambientCol2) * directionLightBrightness;

    // RESULTING COLOR //

    vec3 result = dirLightResult + pointLightResult;

    FragColor = vec4(result, 1.0) * texture(tex0, texCoord);  

}