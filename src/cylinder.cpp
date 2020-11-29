#include <cylinder.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <math.h>
#include <iostream>

Cylinder::Cylinder(float baseRad, float topRad, float height, int sectors,
        int stacks, const Material &material) : PrimitiveMesh(material),
        baseRadius(baseRad), topRadius(topRad), height(height), 
        sectorCount(sectors),  stackCount(stacks) {
    buildUnitCircleVertices();
    buildVertices();
}

void Cylinder::buildVertices() {
    clearArrays();

    float x, y, z; //vertex pos
    float radius; //for each stack

    std::vector<float> sideNormals = getSideNormals();

    for(int i = 0; i <= stackCount; ++i) {
        z = -(height * 0.5f) + (float)i / stackCount * height;
        radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);
        float t = 1.0f - (float)i / stackCount;   // top-to-bottom

        for(int j = 0, k = 0; j <= sectorCount; ++j, k += 3) {
            x = unitCircleVertices[k];
            y = unitCircleVertices[k + 1];

            vertices.push_back(glm::vec3(x * radius, y * radius, z));
            normals.push_back(glm::vec3(sideNormals[k], sideNormals[k + 1], 
                    sideNormals[k + 2]));
            texCoord.push_back(glm::vec2((float)j / sectorCount, t));
        }
    }

    unsigned int baseVertexIndex = (unsigned int)vertices.size();
    z = -height * 0.5f;
    vertices.push_back(glm::vec3(0, 0, z));
    normals.push_back(glm::vec3(0, 0, -1));
    texCoord.push_back(glm::vec2(0.5f, 0.5f));
    for(int i = 0, j = 0; i < sectorCount; ++i, j += 3) {
        x = unitCircleVertices[j];
        y = unitCircleVertices[j+1];
        vertices.push_back(glm::vec3(x * baseRadius, y * baseRadius, z));
        normals.push_back(glm::vec3(0, 0, -1));
        texCoord.push_back(glm::vec2(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f));
    }

    unsigned int topVertexIndex = (unsigned int)vertices.size();
    z = height * 0.5f;
    vertices.push_back(glm::vec3(0, 0, z));
    normals.push_back(glm::vec3(0, 0, 1));
    texCoord.push_back(glm::vec2(0.5f, 0.5f));
    for(int i = 0, j = 0; i < sectorCount; ++i, j += 3) {
        x = unitCircleVertices[j];
        y = unitCircleVertices[j+1];
        vertices.push_back(glm::vec3(x * topRadius, y * topRadius, z));
        normals.push_back(glm::vec3(0, 0, 1));
        texCoord.push_back(glm::vec2(x * 0.5f + 0.5f, -y * 0.5f + 0.5f));
    }

    //indices for sides
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;
    
        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            addIndices(k1, k1 + 1, k2);
            addIndices(k2, k1 + 1, k2 + 1);
        }
    }

    for(int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k) {
        if(i < (sectorCount - 1)) {
            addIndices(baseVertexIndex, k + 1, k);
        } else {
            addIndices(baseVertexIndex, baseVertexIndex + 1, k);
        } // last triangle            
    }

    for(int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k) {
        if(i < (sectorCount - 1)) {
            addIndices(topVertexIndex, k, k + 1);
        } else {
            addIndices(topVertexIndex, k, topVertexIndex + 1);
        }   
    }
}

std::vector<float> Cylinder::getSideNormals() {
    const float PI = acos(-1);
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    // compute the normal vector at 0 degree first
    // tanA = (baseRadius-topRadius) / height
    float zAngle = atan2(baseRadius - topRadius, height);
    float x0 = cos(zAngle);     // nx
    float y0 = 0;               // ny
    float z0 = sin(zAngle);     // nz

    std::vector<float> normals;
    for(int i = 0; i <= sectorCount; ++i) {
        sectorAngle = i * sectorStep;
        normals.push_back(cos(sectorAngle)*x0 - sin(sectorAngle)*y0);   // nx
        normals.push_back(sin(sectorAngle)*x0 + cos(sectorAngle)*y0);   // ny
        normals.push_back(z0);  // nz
    }

    return normals;
}

void Cylinder::buildUnitCircleVertices() {
    const float PI = acos(-1);
    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float>().swap(unitCircleVertices);
    for(int i = 0; i <= sectorCount; ++i) {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(cos(sectorAngle)); // x
        unitCircleVertices.push_back(sin(sectorAngle)); // y
        unitCircleVertices.push_back(0);                // z
    }
}
