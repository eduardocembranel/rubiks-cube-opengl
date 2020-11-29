#include <windowWrapper.hpp>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

WindowWrapper::WindowWrapper(int width, int height, const std::string &winTittle) :
        width(width), height(height), lastX(width/2.0f), lastY(height/2.0f) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, winTittle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw "Failed to initialize GLAD";
    } 

    //config global opengl stats
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_MULTISAMPLE );
    glfwWindowHint(GLFW_SAMPLES, 8);
    glEnable(GL_MULTISAMPLE);  

    //make current windowWrapper as user pointer
    glfwSetWindowUserPointer(window, this);

    //set callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

void WindowWrapper::windowSizeCallback(GLFWwindow *window, int width, int height) {
    void *data = glfwGetWindowUserPointer(window);
    WindowWrapper *w = static_cast<WindowWrapper *>(data);

    w->width = width;
    w->height = height;
    w->cube->transformCube.updateProjection(width, height);
}

void WindowWrapper::mouseButtonCallback(GLFWwindow* window, int button, 
        int action, int mods) {
    void *data = glfwGetWindowUserPointer(window);
    WindowWrapper *w = static_cast<WindowWrapper *>(data);

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        w->cube->transformCube.arcball.animating = true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        w->cube->transformCube.arcball.animating = false;
    }
}

void WindowWrapper::mouseCallback(GLFWwindow* window, double currX, double currY) {
    void *data = glfwGetWindowUserPointer(window);
    WindowWrapper *w = static_cast<WindowWrapper *>(data);    

    if (w->cube->transformCube.arcball.animating) {
        w->cube->transformCube.arcball.rotate(currX, currY, w->lastX, w->lastY, w->width, w->height);
    }

    w->lastX = currX;
    w->lastY = currY;
}

void WindowWrapper::framebufferSizeCallback(GLFWwindow *window, int width, 
        int height) {
    glViewport(0, 0, width, height);
}

void WindowWrapper::scrollCallback(GLFWwindow *window, double xOff, double yOff) {
    void *data = glfwGetWindowUserPointer(window);
    WindowWrapper *w = static_cast<WindowWrapper *>(data);
    
    w->cube->transformCube.updateScale(yOff);
}

void WindowWrapper::processInputs() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

bool WindowWrapper::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void WindowWrapper::swapBuffers() const {
    glfwSwapBuffers(window);
}

void WindowWrapper::terminate() const {
    glfwTerminate();
}

void WindowWrapper::pollEvents() const {
    glfwPollEvents();
}