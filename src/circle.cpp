#include <circle.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Circle::Circle(float radius, int sectors, const Material &material) 
        : PrimitiveMesh(material), radius(radius), sectorCount(sectors) {
    buildUnitCircleVertices();
    buildVertices();
}

void Circle::buildVertices() {
    clearArrays();

    float diam = radius*2.0f;
    glm::vec3 zAxis(0.0f, 0.0f, 1.0f);

    vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    texCoord.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
    normals.push_back(zAxis);

    for(int i = 0, j = 0; i < sectorCount; ++i, j += 3) {
        float x = unitCircleVertices[j] * radius;
        float y = unitCircleVertices[j + 1] * radius;
        float s = (x + radius)/diam;
        float t = (y + radius)/diam;
        
        vertices.push_back(glm::vec3(x, y, 0.0f));
        texCoord.push_back(glm::vec2(s, t));
        normals.push_back(zAxis);
    }

    for(int i = 0, k = 1; i < sectorCount; ++i, ++k) {
        if(i < sectorCount - 1) {
            addIndices(0, k + 1, k);
        } else {
            addIndices(0, 1, k);
        } // last triangle            
    }
}

void Circle::buildUnitCircleVertices() {
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
