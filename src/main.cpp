#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <shader.h>
#include <windowWrapper.hpp>

#include <cubieView.hpp>
#include <sphere.hpp>
#include <cylinder.hpp>
#include <sticker.hpp>
#include <rubiksCubeView.hpp>

#include <light.hpp>

#include <memory>

int main() {
    WindowWrapper w(1920, 1080, "title");  

    Texture teste("../resources/textures/foz.png", GL_RGBA);
    Texture teste2("../resources/textures/pti.png", GL_RGBA);
    Texture teste3("../resources/textures/itaipu.png", GL_RGBA);
    Texture teste4("../resources/textures/unioeste.png", GL_RGBA);
    Texture teste5("../resources/textures/parana.png", GL_RGBA);

    Material black(glm::vec3(0.05f), glm::vec3(0.01f, 0.01f, 0.01f), 
            glm::vec3(0.9f), 16.0f);

    Material green(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(0.3, 1.0, 0.3), 
                    glm::vec3(0.45, 0.55, 0.45), 
                    0.50f * 128);

    Material red(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(1.0, 0.0, 0.0), 
                    glm::vec3(0.7, 0.6, 0.7), 
                    0.50f * 128);

    Material yellow(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(1.0, 1.0, 0.0), 
                    glm::vec3(0.6, 0.6, 0.5), 
                    0.50f * 128);

    Material blue(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(0.0, 0.3, 1.0), 
                    glm::vec3(0.6, 0.6, 0.6), 
                    0.50f * 128);

    Material orange(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(1.0, 0.5, 0.0), 
                    glm::vec3(0.6, 0.6, 0.6), 
                    0.50f * 128);

    Material white(glm::vec3(0.15, 0.15, 0.15), 
                    glm::vec3(1.0, 1.0, 1.0), 
                    glm::vec3(0.7, 0.7, 0.7), 
                    0.50f * 128);

    std::vector<Material> materials;
    materials.push_back(black);
    materials.push_back(green);
    materials.push_back(red);
    materials.push_back(yellow);
    materials.push_back(blue);
    materials.push_back(orange);
    materials.push_back(white);

    w.cube = std::unique_ptr<RubiksCubeView>(
            new RubiksCubeView(w.width, w.height, materials));
    w.cube->loadToBuffer();

    Shader shader("../shader/simple.vs", "../shader/simple.fs");
    shader.use();

    Light light(glm::vec3(1.0f, 1.0f, 15.0f),
                glm::vec3(0.2f),
                glm::vec3(0.9f),
                glm::vec3(1.0f));
                
    shader.setVec3("light.position", light.position);
    shader.setVec3("light.ambient", light.ambient);
    shader.setVec3("light.diffuse", light.diffuse);
    shader.setVec3("light.specular", light.specular);
        
    shader.setVec3("cameraPos", w.cube->transformCube.getCameraPos());

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    ///render loop
    while(!w.shouldClose()) {
        w.processInputs();

        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
                // printf and reset timer
                printf("%f ms/frame\n", 1000.0/double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
        }

        //rendering stuffs
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        shader.setMat4("arcball", w.cube->transformCube.arcball.getRotation()); 
        shader.setMat4("model",  w.cube->transformCube.getModel());
        shader.setMat4("view",  w.cube->transformCube.getView()); 
        shader.setMat4("projection", w.cube->transformCube.getProjection());

        w.cube->draw(shader);

        w.pollEvents(); 
        w.swapBuffers();
    }
    w.terminate();
    return 0;
}
