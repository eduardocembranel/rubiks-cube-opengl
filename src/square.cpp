#include <square.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Square::Square(float size, const Material &material) : PrimitiveMesh(material),
        size(size) {
    buildVertices();
}

void Square::buildVertices() {
    clearArrays();

    float halfSize = size/2.0f;

    vertices.push_back(glm::vec3(-halfSize, 0.0f, -halfSize));
    vertices.push_back(glm::vec3(-halfSize, 0.0f, halfSize));
    vertices.push_back(glm::vec3(halfSize, 0.0f, -halfSize));
    vertices.push_back(glm::vec3(halfSize, 0.0f, halfSize));

    texCoord.push_back(glm::vec2(0.0f, 1.0f));
    texCoord.push_back(glm::vec2(0.0f, 0.0f));
    texCoord.push_back(glm::vec2(1.0f, 1.0f));
    texCoord.push_back(glm::vec2(1.0f, 0.0f));

    glm::vec3 y(0.0f, 1.0f, 0.0f);

    normals.push_back(y);
    normals.push_back(y);
    normals.push_back(y);
    normals.push_back(y);

    addIndices(0, 1, 2);
    addIndices(1, 2, 3);
}
