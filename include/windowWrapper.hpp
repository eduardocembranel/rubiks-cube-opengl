#ifndef WINDOW_WRAPPER_HPP
#define WINDOW_WRAPPER_HPP

#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <arcball.hpp>
#include <transformCube.hpp>
#include <rubiksCubeView.hpp>

#include <shader.h>

class WindowWrapper {
    public:
        WindowWrapper(int, int, const std::string &);
        GLFWwindow *window;
        std::unique_ptr<RubiksCubeView> cube;

        int width;
        int height;
        int lastX;
        int lastY;

        void render(const Shader &);

        void processInputs();

        void swapBuffers() const;
        void pollEvents() const;
        bool shouldClose() const;
        void terminate() const;

    private:
        static void framebufferSizeCallback(GLFWwindow *, int, int);
        static void mouseCallback(GLFWwindow *, double, double);
        static void windowSizeCallback(GLFWwindow *, int, int);
        static void mouseButtonCallback(GLFWwindow *, int, int, int);    
        static void scrollCallback(GLFWwindow *, double, double);
        static void keyCallback(GLFWwindow *, int, int, int, int);
};

#endif //!WINDOW_WRAPPER_HPP
