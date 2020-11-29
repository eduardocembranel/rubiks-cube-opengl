#include <arcball.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <math.h>

Arcball::Arcball() : rotation(1.0f), animating(false), radius(1.0f) {

}

Arcball::Arcball(float radius) : 
        rotation(1.0f), animating(false), radius(radius) {

}

void Arcball::setRadius(float radius) {
    this->radius = radius;
}

glm::mat4 Arcball::getRotation() const {
    return rotation;
}

void Arcball::rotate(int currX, int currY, int lastX, int lastY, 
        int width, int height) {

    float xi = toNDC(currX, 0, width, height);
    float yi = toNDC(currY, 1, width, height);
    float zi = calculateZAxis(xi, yi);  

    float xf = toNDC(lastX, 0, width, height);
    float yf = toNDC(lastY, 1, width, height);
    float zf = calculateZAxis(xf, yf);

    glm::vec3 v1(glm::normalize(glm::vec3(xi, yi, zi)));
    glm::vec3 v2(glm::normalize(glm::vec3(xf, yf, zf)));
    glm::vec3 rotAxis = glm::cross(v1, v2);
    float rotAngle = -1*acos(glm::dot(v1, v2));
    rotAngle = isnan(rotAngle) ? 0.0f : rotAngle;

    glm::quat q = glm::angleAxis(rotAngle, glm::normalize(rotAxis));
    rotation = glm::toMat4(q) * rotation;

   // std::cout << rotAxis.x << " " << rotAxis.y << " " << rotAxis.z << "\n";
   // std::cout << "angle(deg): " << glm::degrees(rotAngle) << "\n";
}

//mudar isso aqui pra passar um vec2 e retornar um vec2
//colocar isso em outra classe
float Arcball::toNDC(float pos, int opt, int width, int height) {
    if (opt == 0) {
        return (pos/(float)width) * 2.0f - 1.0f;
    }
    return (1 - pos/(float)height) * 2.0f - 1.0f;
}

float Arcball::calculateZAxis(float x, float y) {
    float sqRadius = radius*radius;
    if (x*x + y*y <= sqRadius/2.0f) {
        return sqrt(sqRadius - (x*x + y*y));
    }
    return (sqRadius/2.0f)/sqrt(x*x + y*y);
}
