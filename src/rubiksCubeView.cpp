#include <rubiksCubeView.hpp>
#include <material.hpp>
#include <texture.hpp>

RubiksCubeView::RubiksCubeView(int width, int height, 
        const std::vector<Material> &materials) : transformCube(width, height) {
    initCubies(materials);
}

void RubiksCubeView::initCubies(const std::vector<Material> &materials) {
    glm::vec3 a(-0.2, -0.2, -0.2), b(0.2, 0.2, 0.2);
    float transStep = 0.401f;
    float edgeRadius = 0.02f;

    //9 bottom cubies
    CubieView b1(a, b, edgeRadius, materials[0]);
    b1.addSticker(materials[4], "B", 9);
    b1.addSticker(materials[5], "L", 7);
    b1.addSticker(materials[3], "D", 7);
    b1.translate(glm::vec3(-transStep, -transStep, -transStep));
    cubies.push_back(b1);
 
    CubieView b2(a, b, edgeRadius, materials[0]);
    b2.addSticker(materials[4], "B", 7);
    b2.addSticker(materials[3], "D", 9);
    b2.addSticker(materials[2], "R", 9);
    b2.translate(glm::vec3(transStep, -transStep, -transStep));
    cubies.push_back(b2);

    CubieView b3(a, b, edgeRadius, materials[0]);
    b3.addSticker(materials[4], "B", 8);
    b3.addSticker(materials[3], "D", 8);
    b3.translate(glm::vec3(0.0f, -transStep, -transStep));
    cubies.push_back(b3);

    CubieView b4(a, b, edgeRadius, materials[0]);
    b4.addSticker(materials[1], "F", 7);
    b4.addSticker(materials[5], "L", 9);
    b4.addSticker(materials[3], "D", 1);
    b4.translate(glm::vec3(-transStep, -transStep, transStep));
    cubies.push_back(b4);

    CubieView b5(a, b, edgeRadius, materials[0]);
    b5.addSticker(materials[1], "F", 9);
    b5.addSticker(materials[3], "D", 3);
    b5.addSticker(materials[2], "R", 7);
    b5.translate(glm::vec3(transStep, -transStep, transStep));
    cubies.push_back(b5);

    CubieView b6(a, b, edgeRadius, materials[0]);
    b6.addSticker(materials[1], "F", 8);
    b6.addSticker(materials[3], "D", 2);
    b6.translate(glm::vec3(0.0f, -transStep, transStep));
    cubies.push_back(b6);

    CubieView b7(a, b, edgeRadius, materials[0]);
    b7.addSticker(materials[5], "L", 8);
    b7.addSticker(materials[3], "D", 4);
    b7.translate(glm::vec3(-transStep, -transStep, 0.0f));
    cubies.push_back(b7);

    CubieView b8(a, b, edgeRadius, materials[0]);
    b8.addSticker(materials[2], "R", 8);
    b8.addSticker(materials[3], "D", 6);
    b8.translate(glm::vec3(transStep, -transStep, 0.0f));
    cubies.push_back(b8);

    CubieView b9(a, b, edgeRadius, materials[0]);
    b9.addSticker(materials[3], "D", 5);
    b9.translate(glm::vec3(0.0f, -transStep, 0.0f));
    cubies.push_back(b9);

    //9 top cubies
    CubieView t1(a, b, edgeRadius, materials[0]);
    t1.addSticker(materials[4], "B", 3);
    t1.addSticker(materials[5], "L", 1);
    t1.addSticker(materials[6], "U", 1);
    t1.translate(glm::vec3(-transStep, transStep, -transStep));
    cubies.push_back(t1);

    CubieView t2(a, b, edgeRadius, materials[0]);
    t2.addSticker(materials[4], "B", 1);
    t2.addSticker(materials[6], "U", 3);
    t2.addSticker(materials[2], "R", 3);
    t2.translate(glm::vec3(transStep, transStep, -transStep));
    cubies.push_back(t2);

    CubieView t3(a, b, edgeRadius, materials[0]);
    t3.addSticker(materials[4], "B", 2);
    t3.addSticker(materials[6], "U", 2);
    t3.translate(glm::vec3(0.0f, transStep, -transStep));
    cubies.push_back(t3);

    CubieView t4(a, b, edgeRadius, materials[0]);
    t4.addSticker(materials[1], "F", 1);
    t4.addSticker(materials[5], "L", 3);
    t4.addSticker(materials[6], "U", 7);
    t4.translate(glm::vec3(-transStep, transStep, transStep));
    cubies.push_back(t4);

    CubieView t5(a, b, edgeRadius, materials[0]);
    t5.addSticker(materials[1], "F", 3);
    t5.addSticker(materials[6], "U", 9);
    t5.addSticker(materials[2], "R", 1);
    t5.translate(glm::vec3(transStep, transStep, transStep));
    cubies.push_back(t5);

    CubieView t6(a, b, edgeRadius, materials[0]);
    t6.addSticker(materials[1], "F", 2);
    t6.addSticker(materials[6], "U", 8);
    t6.translate(glm::vec3(0.0f, transStep, transStep));
    cubies.push_back(t6);

    CubieView t7(a, b, edgeRadius, materials[0]);
    t7.addSticker(materials[5], "L", 2);
    t7.addSticker(materials[6], "U", 4);
    t7.translate(glm::vec3(-transStep, transStep, 0.0f));
    cubies.push_back(t7);

    CubieView t8(a, b, edgeRadius, materials[0]);
    t8.addSticker(materials[2], "R", 2);
    t8.addSticker(materials[6], "U", 6);
    t8.translate(glm::vec3(transStep, transStep, 0.0f));
    cubies.push_back(t8);

    CubieView t9(a, b, edgeRadius, materials[0]);
    t9.addSticker(materials[6], "U", 5);
    t9.translate(glm::vec3(0.0f, transStep, 0.0f));
    cubies.push_back(t9);

    //middle cubies
    CubieView m1(a, b, edgeRadius, materials[0]);
    m1.addSticker(materials[5], "L", 5);
    m1.translate(glm::vec3(-transStep, 0.0f, 0.0f));
    cubies.push_back(m1);

    CubieView m2(a, b, edgeRadius, materials[0]);
    m2.addSticker(materials[2], "R", 5);
    m2.translate(glm::vec3(transStep, 0.0f, 0.0f));
    cubies.push_back(m2);

    CubieView m3(a, b, edgeRadius, materials[0]);
    m3.addSticker(materials[4], "B", 6);
    m3.addSticker(materials[5], "L", 4);
    m3.translate(glm::vec3(-transStep, 0.0f, -transStep));
    cubies.push_back(m3);

    CubieView m4(a, b, edgeRadius, materials[0]);
    m4.addSticker(materials[4], "B", 5);
    m4.translate(glm::vec3(0.0f, 0.0f, -transStep));
    cubies.push_back(m4);

    CubieView m5(a, b, edgeRadius, materials[0]);
    m5.addSticker(materials[4], "B", 4);
    m5.addSticker(materials[2], "R", 6);
    m5.translate(glm::vec3(transStep, 0.0f, -transStep));
    cubies.push_back(m5);

    CubieView m6(a, b, edgeRadius, materials[0]);
    m6.addSticker(materials[1], "F", 4);
    m6.addSticker(materials[5], "L", 6);
    m6.translate(glm::vec3(-transStep, 0.0f, transStep));
    cubies.push_back(m6);

    CubieView m7(a, b, edgeRadius, materials[0]);
    m7.addSticker(materials[1], "F", 5);
    m7.translate(glm::vec3(0.0f, 0.0f, transStep));
    cubies.push_back(m7);

    CubieView m8(a, b, edgeRadius, materials[0]);
    m8.addSticker(materials[1], "F", 6);
    m8.addSticker(materials[2], "R", 4);
    m8.translate(glm::vec3(transStep, 0.0f, transStep));
    cubies.push_back(m8);
}

void RubiksCubeView::loadToBuffer() {
    for(int i = 0; i < cubies.size(); ++i) {
        cubies[i].loadToBuffer();
    }
}

void RubiksCubeView::draw(const Shader &shader) {
    for(int i = 0; i < cubies.size(); ++i) {
        cubies[i].draw(shader);
    }
}
