#include <material.hpp>

Material::Material() :
        ambient(glm::vec3(0.0f)), 
        diffuse(glm::vec3(0.0f)), 
        specular(glm::vec3(0.0f)), 
        shininess(0.0f),
        texture(nullptr) {

}

Material::Material(const Material &other) :
        ambient(other.ambient), 
        diffuse(other.diffuse), 
        specular(other.specular), 
        shininess(other.shininess) {
    if (!other.texture) {
        texture = nullptr;
    } else {
        texture = std::unique_ptr<Texture>(new Texture(*other.texture));
    }
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float shininess) : 
        ambient(ambient), 
        diffuse(diffuse), 
        specular(specular), 
        shininess(shininess),
        texture(nullptr) {

}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        float shininess, Texture texture) : 
        ambient(ambient), 
        diffuse(diffuse), 
        specular(specular), 
        shininess(shininess),
        texture(new Texture(texture)) {

}
