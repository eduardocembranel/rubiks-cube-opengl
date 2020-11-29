#include <transformCube.hpp>

TransformCube::TransformCube(int width, int height) : arcball(0.4f) {
    updateProjection(width, height);

    cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
    glm::vec3 origin(0.0f, 0.0f, 0.0f);
    glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis(0.0f, 1.0f, 0.0f);

    view = glm::lookAt(cameraPos, origin, yAxis);

    glm::quat q1 = glm::angleAxis(glm::radians(-45.0f), yAxis);
    glm::quat q2 = glm::angleAxis(glm::radians(45.0f), xAxis);

    rotate = glm::toMat4(q2) * glm::toMat4(q1);
    scale  = glm::vec3(1.0f, 1.0f, 1.0f);
    model  = glm::scale(rotate, scale);
}

void TransformCube::updateProjection(int width, int height) {
    projection = glm::perspective(glm::radians(45.0f), 
            width/(float)height, 0.1f, 100.0f);
}

void TransformCube::updateScale(int opt) {
    if ((opt == -1 && scale.x > 0.2) || (opt == 1 && scale.x < 2.0)) {
        scale.x += (opt * 0.1);
        scale.y += (opt * 0.1);
        scale.z += (opt * 0.1);
        model = glm::scale(rotate, scale);
    }

    arcball.setRadius(scale.x/2.0f);
}

glm::mat4 TransformCube::getModel() const {
    return model;
}

glm::mat4 TransformCube::getView() const {
    return view;
}

glm::mat4 TransformCube::getProjection() const {
    return projection;
}

glm::vec3 TransformCube::getCameraPos() const {
    return cameraPos;
}
