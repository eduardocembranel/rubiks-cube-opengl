#ifndef TRANSFORM_CUBE_HPP
#define TRANSFORM_CUBE_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <arcball.hpp>

class TransformCube {
    public:
        TransformCube(int, int);
        void updateProjection(int, int);
        void updateScale(int);

        glm::mat4 getModel() const;
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;
        glm::vec3 getCameraPos() const;

        Arcball arcball;

    private:
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        glm::vec3 scale;
        glm::mat4 rotate;

        glm::vec3 cameraPos;
};

#endif //!TRANSFORM_CUBE_HPP
