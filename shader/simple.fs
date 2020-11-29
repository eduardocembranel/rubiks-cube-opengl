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

vec3 getAmbient() {
    if (!material.hasTexture) {
        return light.ambient * material.ambient;
    } else {
        return light.ambient * vec3(texture(material.diffuseTexture, texCoord));
    }
}

vec3 getDiffuse(float diff) {
    if (!material.hasTexture) {
        return light.diffuse * (diff * material.diffuse);
    } else {
        return light.diffuse * diff * vec3(texture(material.diffuseTexture, texCoord));
    }
}

vec3 getSpecular(float spec) {
    return light.specular * (spec * material.specular);
}

void main()
{   
    //ambient
    vec3 ambient = getAmbient();

    //diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = getDiffuse(diff);

    // specular
    vec3 viewDir = normalize(cameraPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = getSpecular(spec);

    FragColor = vec4(ambient + diffuse + specular, 1.0);

}
