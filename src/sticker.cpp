#include <sticker.hpp>

#include <iostream>

Sticker::Sticker(float cornerRadius, float size, const Material &material) {
    float diam = 2.0f*cornerRadius; 
    float size2 = size - diam;
    float transCircle = size2/2.0f;
    float propCirc = diam/size;
    float propSq = size2/size;

    Circle cLB(cornerRadius, 36, material);
    cLB.translate(glm::vec3(-transCircle, -transCircle, 0.0f));
    mapTexCoordCorners(cLB, propCirc, 1);
    corners.push_back(cLB);

    Circle cRB(cornerRadius, 36, material);
    cRB.translate(glm::vec3(transCircle, -transCircle, 0.0f));
    mapTexCoordCorners(cRB, propCirc, 2);
    corners.push_back(cRB);

    Circle cLT(cornerRadius, 36, material);
    cLT.translate(glm::vec3(-transCircle, transCircle, 0.0f));
    mapTexCoordCorners(cLT, propCirc, 3);
    corners.push_back(cLT);

    Circle cRT(cornerRadius, 36, material);
    cRT.translate(glm::vec3(transCircle, transCircle, 0.0f));
    mapTexCoordCorners(cRT, propCirc, 4);
    corners.push_back(cRT);

    glm::vec3 xAxis(1.0f, 0.0f, 0.0f);

    Square sqTop(size2, material);
    sqTop.rotate(xAxis, glm::radians(90.0f));
    sqTop.translate(glm::vec3(0.0f, cornerRadius, 0.0f));
    mapTexCoordBody(sqTop, propCirc, propSq, 3);
    body.push_back(sqTop);

    Square sqBottom(size2, material);
    sqBottom.rotate(xAxis, glm::radians(90.0f));
    sqBottom.translate(glm::vec3(0.0f, -cornerRadius, 0.0f));
    mapTexCoordBody(sqBottom, propCirc, propSq, 2);
    body.push_back(sqBottom);

    Square sqRight(size2, material);
    sqRight.rotate(xAxis, glm::radians(90.0f));
    sqRight.translate(glm::vec3(cornerRadius, 0.0f, 0.0f));
    mapTexCoordBody(sqRight, propCirc, propSq, 4);
    body.push_back(sqRight);

    Square sqLeft(size2, material);
    sqLeft.rotate(xAxis, glm::radians(90.0f));
    sqLeft.translate(glm::vec3(-cornerRadius, 0.0f, 0.0f));
    mapTexCoordBody(sqLeft, propCirc, propSq, 1);
    body.push_back(sqLeft);
}

void Sticker::mapTexCoordCorners(Circle &circle, float propCirc, int opt) {
    float offset = 1.0f - propCirc;

    for(unsigned int i = 0; i < circle.texCoord.size(); ++i) {
        circle.texCoord[i] *= propCirc;

        if (opt == 2) { //lower right
            circle.texCoord[i].x += offset;
        } else if (opt == 3) { //upper left
            circle.texCoord[i].y += offset;
        } else if (opt == 4) { //upper right
            circle.texCoord[i].x += offset;
            circle.texCoord[i].y += offset;
        } 
    }
}

void Sticker::mapTexCoordBody(Square &square, float propCirc, float propSq, 
        int opt) {
    for(int i = 0; i < square.texCoord.size(); ++i) {
        square.texCoord[i] *= propSq;

        if (opt == 1) { //left
            square.texCoord[i].y += propCirc/2.0f;
        } else if (opt == 2) { //bottom
            square.texCoord[i].x += propCirc/2.0f;
        } else if (opt == 3) { //top
            square.texCoord[i].x += propCirc/2.0f;
            square.texCoord[i].y += propCirc;
        } else if (opt == 4) { //right
            square.texCoord[i].x += propCirc;
            square.texCoord[i].y += propCirc/2.0f;
        }
    }
}

void Sticker::mapTexCoordToLocation(int loc) {
    for(int i = 0; i < corners.size(); ++i) {
        mapTexCoordToLocationAux(corners[i], loc);
    }
    for(int i = 0; i < body.size(); ++i) {
        mapTexCoordToLocationAux(body[i], loc);
    }
}

void Sticker::mapTexCoordToLocationAux(Circle &obj, int loc) {
    float propMiddle = 0.0566f;
    float propSticker = 0.2956f;
    float jump1 = propMiddle + propSticker;
    float jump2 = 2*jump1;

    for(unsigned int i = 0; i < obj.texCoord.size(); ++i) {
        obj.texCoord[i] *= propSticker;

        // 1|2|3
        // 4|5|6
        // 7|8|9
        if (loc == 1) { 
            obj.texCoord[i].y += jump2;
        } else if (loc == 2) {
            obj.texCoord[i].y += jump2;
            obj.texCoord[i].x += jump1;
        } else if (loc == 3) {
            obj.texCoord[i].y += 2*propMiddle + 2*propSticker;
            obj.texCoord[i].x += jump2;
        } else if (loc == 4) {
            obj.texCoord[i].y += jump1;
        } else if (loc == 5) {
            obj.texCoord[i].y += jump1;
            obj.texCoord[i].x += jump1;
        } else if (loc == 6) {
            obj.texCoord[i].y += jump1;
            obj.texCoord[i].x += jump2;
        } else if (loc == 7) {
            //
        } else if (loc == 8) {
            obj.texCoord[i].x += jump1;
        } else if (loc == 9) {
            obj.texCoord[i].x += jump2;
        }
    }    
}

void Sticker::mapTexCoordToLocationAux(Square &obj, int loc) {
    float propMiddle = 0.0566f;
    float propSticker = 0.2956f;
    float jump1 = propMiddle + propSticker;
    float jump2 = 2*jump1;

    for(unsigned int i = 0; i < obj.texCoord.size(); ++i) {
        obj.texCoord[i] *= propSticker;

        // 1|2|3
        // 4|5|6
        // 7|8|9
        if (loc == 1) { 
            obj.texCoord[i].y += jump2;
        } else if (loc == 2) {
            obj.texCoord[i].y += jump2;
            obj.texCoord[i].x += jump1;
        } else if (loc == 3) {
            obj.texCoord[i].y += 2*propMiddle + 2*propSticker;
            obj.texCoord[i].x += jump2;
        } else if (loc == 4) {
            obj.texCoord[i].y += jump1;
        } else if (loc == 5) {
            obj.texCoord[i].y += jump1;
            obj.texCoord[i].x += jump1;
        } else if (loc == 6) {
            obj.texCoord[i].y += jump1;
            obj.texCoord[i].x += jump2;
        } else if (loc == 7) {
            //
        } else if (loc == 8) {
            obj.texCoord[i].x += jump1;
        } else if (loc == 9) {
            obj.texCoord[i].x += jump2;
        }
    }    
}

void Sticker::loadToBuffer() {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].loadToBuffer();
    }
    for(int i = 0; i < body.size(); ++i) {
        body[i].loadToBuffer();
    }
}

void Sticker::draw(const Shader &shader) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].draw(shader);
    }
    for(int i = 0; i < body.size(); ++i) {
        body[i].draw(shader);
    }
}

void Sticker::scale(glm::vec3 pos) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].scale(pos);
    }
    for(int i = 0; i < body.size(); ++i) {
        body[i].scale(pos);
    }
}

void Sticker::translate(glm::vec3 pos) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].translate(pos);
    }
    for(int i = 0; i < body.size(); ++i) {
        body[i].translate(pos);
    }
}

void Sticker::rotate(glm::vec3 rotAxis, float rotAngle) {
    for(int i = 0; i < corners.size(); ++i) {
        corners[i].rotate(rotAxis, rotAngle);
    }
    for(int i = 0; i < body.size(); ++i) {
        body[i].rotate(rotAxis, rotAngle);
    }
}
