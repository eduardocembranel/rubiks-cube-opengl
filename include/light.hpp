#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {
    public:
        Light();
        Light(const Light &);
        Light(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
};

#endif //!LIGHT_HPP