#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <texture.hpp>


class Material {
    public:
        Material();
        Material(const Material &);
        Material(glm::vec3, glm::vec3, glm::vec3, float);
        Material(glm::vec3, glm::vec3, glm::vec3, float, Texture);
        
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        std::unique_ptr<Texture> texture;
};

#endif //!MATERIAL_HPP
