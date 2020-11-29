#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;

    bool hasTexture;
    sampler2D diffuseTexture;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

out vec4 FragColor;

void main()
{   

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 ambient;
    vec3 diffuse;
    if (!material.hasTexture) {
        ambient = light.ambient * material.ambient;
        diffuse = light.diffuse * (diff * material.diffuse);
    } else {
        ambient = light.ambient * vec3(texture(material.diffuseTexture, texCoord));
        diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture, texCoord));
    }

    // specular
    vec3 viewDir = normalize(cameraPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}
