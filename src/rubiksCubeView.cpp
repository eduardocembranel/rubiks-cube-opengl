#include <rubiksCubeView.hpp>
#include <material.hpp>
#include <texture.hpp>

#include <iostream>

RubiksCubeView::RubiksCubeView(int width, int height, 
        const std::vector<Material> &materials) : transformCube(width, height),
        rotManager(400.0f) {
    initCubies(materials);
    initFaces();
}

void RubiksCubeView::initCubies(const std::vector<Material> &materials) {
    glm::vec3 a(-0.2, -0.2, -0.2), b(0.2, 0.2, 0.2);
    float transStep = 0.401f;
    float edgeRadius = 0.02f;

    //9 bottom cubies
    std::shared_ptr<CubieView> b1 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b1->addSticker(materials[4], "B", 9);
    b1->addSticker(materials[5], "L", 7);
    b1->addSticker(materials[3], "D", 7);
    b1->translate(glm::vec3(-transStep, -transStep, -transStep));
    cubies.push_back(b1);
 
    std::shared_ptr<CubieView> b2 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b2->addSticker(materials[4], "B", 7);
    b2->addSticker(materials[2], "R", 9);
    b2->addSticker(materials[3], "D", 9);
    b2->translate(glm::vec3(transStep, -transStep, -transStep));
    cubies.push_back(b2);

    std::shared_ptr<CubieView> b3 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b3->addSticker(materials[4], "B", 8);
    b3->addSticker(materials[3], "D", 8);
    b3->translate(glm::vec3(0.0f, -transStep, -transStep));
    cubies.push_back(b3);

    std::shared_ptr<CubieView> b4 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b4->addSticker(materials[1], "F", 7);
    b4->addSticker(materials[5], "L", 9);
    b4->addSticker(materials[3], "D", 1);
    b4->translate(glm::vec3(-transStep, -transStep, transStep));
    cubies.push_back(b4);

    std::shared_ptr<CubieView> b5 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b5->addSticker(materials[1], "F", 9);
    b5->addSticker(materials[2], "R", 7);
    b5->addSticker(materials[3], "D", 3);
    b5->translate(glm::vec3(transStep, -transStep, transStep));
    cubies.push_back(b5);

    std::shared_ptr<CubieView> b6 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b6->addSticker(materials[1], "F", 8);
    b6->addSticker(materials[3], "D", 2);
    b6->translate(glm::vec3(0.0f, -transStep, transStep));
    cubies.push_back(b6);

    std::shared_ptr<CubieView> b7 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b7->addSticker(materials[5], "L", 8);
    b7->addSticker(materials[3], "D", 4);
    b7->translate(glm::vec3(-transStep, -transStep, 0.0f));
    cubies.push_back(b7);

    std::shared_ptr<CubieView> b8 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b8->addSticker(materials[2], "R", 8);
    b8->addSticker(materials[3], "D", 6);
    b8->translate(glm::vec3(transStep, -transStep, 0.0f));
    cubies.push_back(b8);

    std::shared_ptr<CubieView> b9 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    b9->addSticker(materials[3], "D", 5);
    b9->translate(glm::vec3(0.0f, -transStep, 0.0f));
    cubies.push_back(b9);

    //9 top cubies
    std::shared_ptr<CubieView> t1 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t1->addSticker(materials[4], "B", 3);
    t1->addSticker(materials[5], "L", 1);
    t1->addSticker(materials[6], "U", 1);
    t1->translate(glm::vec3(-transStep, transStep, -transStep));
    cubies.push_back(t1);

    std::shared_ptr<CubieView> t2 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t2->addSticker(materials[4], "B", 1);
    t2->addSticker(materials[2], "R", 3);
    t2->addSticker(materials[6], "U", 3);
    t2->translate(glm::vec3(transStep, transStep, -transStep));
    cubies.push_back(t2);

    std::shared_ptr<CubieView> t3 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t3->addSticker(materials[4], "B", 2);
    t3->addSticker(materials[6], "U", 2);
    t3->translate(glm::vec3(0.0f, transStep, -transStep));
    cubies.push_back(t3);

    std::shared_ptr<CubieView> t4 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t4->addSticker(materials[1], "F", 1);
    t4->addSticker(materials[5], "L", 3);
    t4->addSticker(materials[6], "U", 7);
    t4->translate(glm::vec3(-transStep, transStep, transStep));
    cubies.push_back(t4);

    std::shared_ptr<CubieView> t5 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t5->addSticker(materials[1], "F", 3);
    t5->addSticker(materials[2], "R", 1);
    t5->addSticker(materials[6], "U", 9);
    t5->translate(glm::vec3(transStep, transStep, transStep));
    cubies.push_back(t5);

    std::shared_ptr<CubieView> t6 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t6->addSticker(materials[1], "F", 2);
    t6->addSticker(materials[6], "U", 8);
    t6->translate(glm::vec3(0.0f, transStep, transStep));
    cubies.push_back(t6);

    std::shared_ptr<CubieView> t7 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t7->addSticker(materials[5], "L", 2);
    t7->addSticker(materials[6], "U", 4);
    t7->translate(glm::vec3(-transStep, transStep, 0.0f));
    cubies.push_back(t7);

    std::shared_ptr<CubieView> t8 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t8->addSticker(materials[2], "R", 2);
    t8->addSticker(materials[6], "U", 6);
    t8->translate(glm::vec3(transStep, transStep, 0.0f));
    cubies.push_back(t8);

    std::shared_ptr<CubieView> t9 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    t9->addSticker(materials[6], "U", 5);
    t9->translate(glm::vec3(0.0f, transStep, 0.0f));
    cubies.push_back(t9);

    //middle cubies
    std::shared_ptr<CubieView> m1 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m1->addSticker(materials[5], "L", 5);
    m1->translate(glm::vec3(-transStep, 0.0f, 0.0f));
    cubies.push_back(m1);

    std::shared_ptr<CubieView> m2 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m2->addSticker(materials[2], "R", 5);
    m2->translate(glm::vec3(transStep, 0.0f, 0.0f));
    cubies.push_back(m2);

    std::shared_ptr<CubieView> m3 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m3->addSticker(materials[4], "B", 6);
    m3->addSticker(materials[5], "L", 4);
    m3->translate(glm::vec3(-transStep, 0.0f, -transStep));
    cubies.push_back(m3);

    std::shared_ptr<CubieView> m4 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m4->addSticker(materials[4], "B", 5);
    m4->translate(glm::vec3(0.0f, 0.0f, -transStep));
    cubies.push_back(m4);

    std::shared_ptr<CubieView> m5 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m5->addSticker(materials[4], "B", 4);
    m5->addSticker(materials[2], "R", 6);
    m5->translate(glm::vec3(transStep, 0.0f, -transStep));
    cubies.push_back(m5);

    std::shared_ptr<CubieView> m6 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m6->addSticker(materials[1], "F", 4);
    m6->addSticker(materials[5], "L", 6);
    m6->translate(glm::vec3(-transStep, 0.0f, transStep));
    cubies.push_back(m6);

    std::shared_ptr<CubieView> m7 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m7->addSticker(materials[1], "F", 5);
    m7->translate(glm::vec3(0.0f, 0.0f, transStep));
    cubies.push_back(m7);

    std::shared_ptr<CubieView> m8 = std::make_shared<CubieView>(
        a, b, edgeRadius, materials[0]);
    m8->addSticker(materials[1], "F", 6);
    m8->addSticker(materials[2], "R", 4);
    m8->translate(glm::vec3(transStep, 0.0f, transStep));
    cubies.push_back(m8);
}

void RubiksCubeView::initFaces() {
    //face 0: green (front)
    std::shared_ptr<Face> green = std::make_shared<Face>();
    green->cubies.push_back(cubies[12]); //green/orange/white [1]
    green->cubies.push_back(cubies[14]); //green/white        [2]
    green->cubies.push_back(cubies[13]); //green/red/white    [3]
    green->cubies.push_back(cubies[23]); //green/orange       [4]
    green->cubies.push_back(cubies[24]); //green              [5]
    green->cubies.push_back(cubies[25]); //green/red          [6]
    green->cubies.push_back(cubies[3]); //green/orange/yellow [7]
    green->cubies.push_back(cubies[5]); //green/yellow        [8]
    green->cubies.push_back(cubies[4]); //green/red/yellow    [9]

    //face 1: blue (back)
    std::shared_ptr<Face> blue = std::make_shared<Face>();
    blue->cubies.push_back(cubies[9]);  //blue/orange/white  [1]
    blue->cubies.push_back(cubies[20]); //blue/orange        [2]
    blue->cubies.push_back(cubies[0]);  //blue/orange/yellow [3]
    blue->cubies.push_back(cubies[11]); //blue/white         [4]
    blue->cubies.push_back(cubies[21]); //blue/              [5]
    blue->cubies.push_back(cubies[2]);  //blue/yellow        [6]
    blue->cubies.push_back(cubies[10]); //blue/red/white     [7]
    blue->cubies.push_back(cubies[22]); //blue/red           [8]
    blue->cubies.push_back(cubies[1]);  //blue/red/yellow    [9]

    //face 2: orange (left)
    std::shared_ptr<Face> orange = std::make_shared<Face>();
    orange->cubies.push_back(cubies[3]);  //green/orange/yellow [1]
    orange->cubies.push_back(cubies[6]);  //orange/yellow       [2]
    orange->cubies.push_back(cubies[0]);  //blue/orange/yellow  [3]
    orange->cubies.push_back(cubies[23]); //orange/green        [4]
    orange->cubies.push_back(cubies[18]); //orange              [5]
    orange->cubies.push_back(cubies[20]); //orange/blue         [6]
    orange->cubies.push_back(cubies[12]); //green/orange/white  [7]
    orange->cubies.push_back(cubies[15]); //orange/white        [8]
    orange->cubies.push_back(cubies[9]);  //blue/orange/white   [9]
    
    //face 3: red (right)
    std::shared_ptr<Face> red = std::make_shared<Face>();
    red->cubies.push_back(cubies[4]);  //red/green/yellow [1]
    red->cubies.push_back(cubies[25]); //red/green        [2]
    red->cubies.push_back(cubies[13]); //red/green/white  [3]
    red->cubies.push_back(cubies[7]);  //red/yellow       [4]
    red->cubies.push_back(cubies[19]); //red              [5]
    red->cubies.push_back(cubies[16]); //red/white        [6]
    red->cubies.push_back(cubies[1]);  //red/blue/yellow  [7]
    red->cubies.push_back(cubies[22]); //red/blue         [8]
    red->cubies.push_back(cubies[10]); //red/blue/white   [9]
    
    //face 4: white (up)
    std::shared_ptr<Face> white = std::make_shared<Face>();
    white->cubies.push_back(cubies[10]); //white/red/blue     [1]
    white->cubies.push_back(cubies[16]); //white/red          [2]
    white->cubies.push_back(cubies[13]); //white/red/green    [3]
    white->cubies.push_back(cubies[11]); //white/blue         [4]
    white->cubies.push_back(cubies[17]); //white              [5]
    white->cubies.push_back(cubies[14]); //white/green        [6]
    white->cubies.push_back(cubies[9]);  //white/orange/blue  [7]
    white->cubies.push_back(cubies[15]); //white/orange       [8]
    white->cubies.push_back(cubies[12]); //white/orange/green [9]
    
    //face 5: yellow (down)
    std::shared_ptr<Face> yellow = std::make_shared<Face>();
    yellow->cubies.push_back(cubies[1]); //yellow/red/blue     [1]
    yellow->cubies.push_back(cubies[2]); //yellow/blue         [2]
    yellow->cubies.push_back(cubies[0]); //yellow/orange/blue  [3]
    yellow->cubies.push_back(cubies[7]); //yellow/red          [4]
    yellow->cubies.push_back(cubies[8]); //yellow              [5]
    yellow->cubies.push_back(cubies[6]); //yellow/orange       [6]
    yellow->cubies.push_back(cubies[4]); //yellow/green/red    [7]
    yellow->cubies.push_back(cubies[5]); //yellow/green        [8]
    yellow->cubies.push_back(cubies[3]); //yellow/green/orange [9]   

    green->westFace  = orange;
    green->eastFace  = red;
    green->northFace = white;
    green->southFace = yellow; 

    blue->westFace  = white;
    blue->eastFace  = yellow;
    blue->northFace = orange;
    blue->southFace = red;

    orange->westFace  = green;
    orange->eastFace  = blue;
    orange->northFace = yellow;
    orange->southFace = white;

    red->westFace  = yellow;
    red->eastFace  = white;
    red->northFace = green;
    red->southFace = blue;

    white->westFace  = blue;
    white->eastFace  = green;
    white->northFace = red;
    white->southFace = orange;

    yellow->westFace  = red;
    yellow->eastFace  = orange;
    yellow->northFace = blue;
    yellow->southFace = green;

    faces.push_back(green);
    faces.push_back(blue);
    faces.push_back(orange);
    faces.push_back(red);
    faces.push_back(white);
    faces.push_back(yellow);
}

//0: 45 dg, 1: -45, 2: 180
void RubiksCubeView::rotateFace(int faceIdx, int opt) {
    updateFaces(faceIdx, opt);
    updateModels(faceIdx, opt);
}

void RubiksCubeView::updateFaces(int faceIdx, int opt) {
    auto face = faces[faceIdx];
    
    if (opt == 0) {
        //swap corners
        auto tmp = face->cubies[0];
        face->cubies[0] = face->cubies[6];
        face->cubies[6] = face->cubies[8];
        face->cubies[8] = face->cubies[2];
        face->cubies[2] = tmp;

        //swap edges
        tmp = face->cubies[1];
        face->cubies[1] = face->cubies[3];
        face->cubies[3] = face->cubies[7];
        face->cubies[7] = face->cubies[5];
        face->cubies[5] = tmp;

        //update neighbor faces
        face->westFace->cubies[6] = face->cubies[0];
        face->westFace->cubies[3] = face->cubies[3];
        face->westFace->cubies[0] = face->cubies[6];
        
        face->eastFace->cubies[2] = face->cubies[2];
        face->eastFace->cubies[1] = face->cubies[5];
        face->eastFace->cubies[0] = face->cubies[8];

        face->northFace->cubies[2] = face->cubies[2];
        face->northFace->cubies[5] = face->cubies[1];
        face->northFace->cubies[8] = face->cubies[0];

        face->southFace->cubies[6] = face->cubies[8];
        face->southFace->cubies[7] = face->cubies[7];
        face->southFace->cubies[8] = face->cubies[6];
    } else if (opt == 1) {

    } else if (opt == 2) {

    }
}

void RubiksCubeView::updateModels(int faceIdx, int opt) {
    auto face = faces[faceIdx];

    glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
    glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
    
    glm::vec3 rotAxis;
    if (faceIdx == 0 || faceIdx == 1) {
        rotAxis = zAxis;
    } else if (faceIdx == 2 || faceIdx == 3) {
        rotAxis = xAxis;
    } else if (faceIdx == 4 || faceIdx == 5) {
        rotAxis = yAxis;
    }

    float rotAngle = (opt != 2) ? 90.0f : 180.0f;
    if (faceIdx == 0 || faceIdx == 3 || faceIdx == 4) rotAngle = -rotAngle;
    if (opt == 1) rotAngle = -rotAngle;

    for(auto &cubie : face->cubies) {
        cubie->rotateModel(rotAxis, glm::radians(rotAngle));
    }
}

void RubiksCubeView::updateModels2(int faceIdx, int opt, float rotAngle) {
    auto face = faces[faceIdx];

    glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
    glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
    glm::vec3 zAxis(0.0f, 0.0f, 1.0f);

    glm::vec3 rotAxis;
    if (faceIdx == 0 || faceIdx == 1) {
        rotAxis = zAxis;
    } else if (faceIdx == 2 || faceIdx == 3) {
        rotAxis = xAxis;
    } else if (faceIdx == 4 || faceIdx == 5) {
        rotAxis = yAxis;
    }

    if (faceIdx == 0 || faceIdx == 3 || faceIdx == 4) rotAngle = -rotAngle;
    if (opt == 1) rotAngle = -rotAngle;

    for(auto &cubie : face->cubies) {
        cubie->rotateModel(rotAxis, glm::radians(rotAngle));
    }

}

void RubiksCubeView::loadToBuffer() {
    for(int i = 0; i < cubies.size(); ++i) {
        cubies[i]->loadToBuffer();
    }
}

void RubiksCubeView::draw(const Shader &shader) {
    for(int i = 0; i < cubies.size(); ++i) {
        cubies[i]->draw(shader);
    }
}
