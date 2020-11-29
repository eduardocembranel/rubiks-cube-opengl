#include <light.hpp>

Light::Light() :
    position(glm::vec3(0.0f)),
    ambient(glm::vec3(0.0f)), 
    diffuse(glm::vec3(0.0f)), 
    specular(glm::vec3(0.0f)) {

}

Light::Light(const Light &other) :
        position(other.position), 
        ambient(other.ambient), 
        diffuse(other.diffuse), 
        specular(other.specular) {
    
}

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse,
        glm::vec3 specular) :
        position(position),
        ambient(ambient), 
        diffuse(diffuse), 
        specular(specular) {

}
