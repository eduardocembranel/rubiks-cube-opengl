#include <cubeRotateManager.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>

#include <iostream>

CubeRotateManager::CubeRotateManager(float animDuration) : 
        animDuration(animDuration), rotating(false), face(0), 
        opt(0), prevTime(0.0f), totalAngle(0.0f),
        accumulatedAngle(0.0f) {

}

void CubeRotateManager::beginRotate(int face, int opt) {
    rotating = true;
    this->face = face;
    this->opt = opt;
    prevTime = glfwGetTime();
    accumulatedAngle = 0.0f;
    totalAngle = (opt != 2) ? 90.0f : 180.0f;
}

float CubeRotateManager::rotateAnimated() {
    float currTime = glfwGetTime();
    float deltaTime = currTime - prevTime;
    double animPercentage = std::min((deltaTime*1000.0f)/animDuration, 1.0f);
    
    float rotAngle = animPercentage * totalAngle;
    rotAngle = (rotAngle + accumulatedAngle > totalAngle) ? 
            totalAngle - accumulatedAngle 
            : rotAngle;
    accumulatedAngle += rotAngle;

    if (accumulatedAngle == totalAngle) {
        rotating = false;
    }

    prevTime = currTime;

    return rotAngle;
}
