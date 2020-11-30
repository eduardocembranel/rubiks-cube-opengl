#include <cubieView.hpp>

#include <iostream>
#include <math.h>

#include <typeinfo>

#include <material.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

//a: lower bottom vertice
//b: upper top vertice
CubieView::CubieView(glm::vec3 a, glm::vec3 b, float edgeRadius,
        const Material &material) : model(1.0f) {

    size = fabs(a.x - b.x);
    glm::vec3 aa = a + edgeRadius;
    glm::vec3 bb = b - edgeRadius;

    std::vector<glm::vec3> cornerVertices = {
        glm::vec3(aa), //LBF
        glm::vec3(bb.x, aa.y, aa.z), //RBF
        glm::vec3(bb.x, aa.y, bb.z), //RBB
        glm::vec3(aa.x, aa.y, bb.z), //LBB
        glm::vec3(aa.x, bb.y, aa.z), //LTF
        glm::vec3(bb.x, bb.y, aa.z), //RTF
        glm::vec3(bb),               //RTB
        glm::vec3(aa.x, bb.y, bb.z)  //LTB
    };

    for(int i = 0; i < 8; ++i) {
        corners.push_back(Sphere(edgeRadius, 30, 30, material));
        corners[i].translate(cornerVertices[i]);
    }

    float edgeHeight = fabs(aa.x - bb.x);

    //4 bottom edges
    for(int i = 0; i < 4; ++i) {
        Cylinder c(edgeRadius, edgeRadius, edgeHeight, 36, 1, material);
        c.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(90.0f));
        c.translate(glm::vec3(cornerVertices[i].x, 0.0f, cornerVertices[i].z));
        edges.push_back(c);
    }

    //bottom left and right edges
    for(int i = 0; i < 2; ++i) {
        Cylinder c(edgeRadius, edgeRadius, edgeHeight, 36, 1, material);
        c.translate(glm::vec3(cornerVertices[i].x, cornerVertices[i].y, 0.0f));
        edges.push_back(c);
    }

    //top left and right edges
    for(int i = 4; i < 6; ++i) {
        Cylinder c(edgeRadius, edgeRadius, edgeHeight, 36, 1, material);
        c.translate(glm::vec3(cornerVertices[i].x, cornerVertices[i].y, 0.0f));
        edges.push_back(c);
    }

    //top front and back edges
    for(int i = 5; i < 7; ++i) {
        Cylinder c(edgeRadius, edgeRadius, edgeHeight, 36, 1, material);
        c.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f));
        c.translate(glm::vec3(0.0f, cornerVertices[i].y, cornerVertices[i].z));
        edges.push_back(c);
    }

    //bottom front and back edges
    for(int i = 1; i < 3; ++i) {
        Cylinder c(edgeRadius, edgeRadius, edgeHeight, 36, 1, material);
        c.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f));
        c.translate(glm::vec3(0.0f, cornerVertices[i].y, cornerVertices[i].z));
        edges.push_back(c);
    }

    float squareSize = fabs(aa.x - bb.x);
    float squareTrans = fabs(a.x - b.x)/2.0f;

    Square faceTop(squareSize, material);
    faceTop.translate(glm::vec3(0.0f, squareTrans, 0.0f));

    Square faceBottom(squareSize, material);
    faceBottom.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(180.0f));
    faceBottom.translate(glm::vec3(0.0f, -squareTrans, 0.0f));

    Square faceFront(squareSize, material);
    faceFront.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(90.0f));
    faceFront.translate(glm::vec3(0.0f, 0.0f, squareTrans));

    Square faceBack(squareSize, material);
    faceBack.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f));
    faceBack.translate(glm::vec3(0.0f, 0.0f, -squareTrans));

    Square faceRight(squareSize, material);
    faceRight.rotate(glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(-90.0f));
    faceRight.translate(glm::vec3(squareTrans, 0.0f, 0.0f));

    Square faceLeft(squareSize, material);
    faceLeft.rotate(glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(90.0f));
    faceLeft.translate(glm::vec3(-squareTrans, 0.0f, 0.0f));

    faces.push_back(faceTop);
    faces.push_back(faceBottom);
    faces.push_back(faceFront);
    faces.push_back(faceBack);
    faces.push_back(faceRight);
    faces.push_back(faceLeft);

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

    /*
    addSticker(green, "F");
    addSticker(blue, "B");
    addSticker(white, "U");
    addSticker(yellow, "D");
    addSticker(red, "R");
    addSticker(orange, "L");
    */
}

//criar funcao buildCube e passar quase todo o contrutor pra ele

void CubieView::loadToBuffer() {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].loadToBuffer();
    }
    for(int i = 0; i < edges.size(); ++i) {
        edges[i].loadToBuffer();
    }
    for(int i = 0; i < faces.size(); ++i) {
        faces[i].loadToBuffer();
    }
    for(int i = 0; i < stickers.size(); ++i) {
        stickers[i].loadToBuffer();
    }
}

void CubieView::draw(const Shader &shader) {
    shader.setMat4("cubieRotate", model);

    for(int i = 0; i < corners.size(); ++i) {
        corners[i].draw(shader);
    }
    for(int i = 0; i < edges.size(); ++i) {
        edges[i].draw(shader);
    }
    for(int i = 0; i < faces.size(); ++i) {
        faces[i].draw(shader);
    }
    for(int i = 0; i < stickers.size(); ++i) {
        stickers[i].draw(shader);
    }
}

void CubieView::addSticker(const Material &stickerMaterial, 
        const std::string &face, int loc) {
    float stickerSize = size * 0.85f;
    float stickerRadius = stickerSize * 0.2f;
    float transStep = size/2.0f + 0.001f;

    Sticker sticker(stickerRadius, stickerSize, stickerMaterial);
    sticker.mapTexCoordToLocation(loc);

    if (face == "F") { //front
        sticker.translate(glm::vec3(0.0f, 0.0f, transStep));
        stickers.push_back(sticker);
    } else if (face == "B") { //back
        sticker.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(180.0f));
        sticker.translate(glm::vec3(0.0f, 0.0f, -transStep));
        stickers.push_back(sticker);
    } else if (face == "R") { //right
        sticker.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f));
        sticker.translate(glm::vec3(transStep, 0.0f, 0.0f));
        stickers.push_back(sticker);
    } else if (face == "L") { //left
        sticker.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-90.0f));
        sticker.translate(glm::vec3(-transStep, 0.0f, 0.0f));
        stickers.push_back(sticker);
    } else if (face == "U") { //up
        sticker.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(-90.0f));
        sticker.translate(glm::vec3(0.0f, transStep, 0.0f));
        stickers.push_back(sticker);
    } else if (face == "D") { //down
        sticker.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(90.0f));
        sticker.translate(glm::vec3(0.0f, -transStep, 0.0f));
        stickers.push_back(sticker);
    }

    //tirar dps
    //buildInterleavedVertices();
}

void CubieView::scale(glm::vec3 sc) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].scale(sc);
    }
    for(int i = 0; i < edges.size(); ++i) {
        edges[i].scale(sc);
    }
    for(int i = 0; i < faces.size(); ++i) {
        faces[i].scale(sc);
    }
    for(int i = 0; i < stickers.size(); ++i) {
        stickers[i].scale(sc);
    }
}

void CubieView::translate(glm::vec3 pos) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].translate(pos);
    }
    for(int i = 0; i < edges.size(); ++i) {
        edges[i].translate(pos);
    }
    for(int i = 0; i < faces.size(); ++i) {
        faces[i].translate(pos);
    }
    for(int i = 0; i < stickers.size(); ++i) {
        stickers[i].translate(pos);
    }
}

void CubieView::rotate(glm::vec3 rotAxis, float rotAngle) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].rotate(rotAxis, rotAngle);
    }
    for(int i = 0; i < edges.size(); ++i) {
        edges[i].rotate(rotAxis, rotAngle);
    }
    for(int i = 0; i < faces.size(); ++i) {
        faces[i].rotate(rotAxis, rotAngle);
    }
    for(int i = 0; i < stickers.size(); ++i) {
        stickers[i].rotate(rotAxis, rotAngle);
    }
}

void CubieView::rotateModel(glm::vec3 rotAxis, float rotAngle) {
    glm::quat q = glm::angleAxis(rotAngle, glm::normalize(rotAxis));
    glm::mat4 rot = glm::toMat4(q);

    model = rot * model;
}

glm::mat4 CubieView::getModel() const {
    return model;
}