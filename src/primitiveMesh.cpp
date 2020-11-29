#include <primitiveMesh.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

PrimitiveMesh::PrimitiveMesh(const Material &material) : material(material) {

}

void PrimitiveMesh::scale(glm::vec3 sc) {
    for(int i = 0; i < vertices.size(); ++i) {
        vertices[i] *= sc;
    }
}

void PrimitiveMesh::translate(glm::vec3 pos) {
    for(int i = 0; i < vertices.size(); ++i) {
        vertices[i] += pos;
    }
}

void PrimitiveMesh::rotate(glm::vec3 rotAxis, float rotAngle) {
    glm::quat q = glm::angleAxis(rotAngle, glm::normalize(rotAxis));
    glm::mat3 rot = glm::toMat3(q);

    for(int i = 0; i < vertices.size(); ++i) {
        vertices[i] = rot * vertices[i];
        normals[i] = glm::normalize(rot * normals[i]);
    }
}

void PrimitiveMesh::buildInterleavedVertices() {
    std::vector<float>().swap(interleavedVertices);

    for(int i = 0; i < vertices.size(); ++i) {
        interleavedVertices.push_back(vertices[i].x);
        interleavedVertices.push_back(vertices[i].y);
        interleavedVertices.push_back(vertices[i].z);

        interleavedVertices.push_back(normals[i].x);
        interleavedVertices.push_back(normals[i].y);
        interleavedVertices.push_back(normals[i].z);

        interleavedVertices.push_back(texCoord[i].x);
        interleavedVertices.push_back(texCoord[i].y);
    }
}

const std::vector<float> PrimitiveMesh::getInterleavedVertices() const {
    return interleavedVertices;
}

std::vector<float> &PrimitiveMesh::getInterleavedVertices() {
    return interleavedVertices;
}

std::vector<unsigned int> PrimitiveMesh::getIndices() const {
    return indices;
}

void PrimitiveMesh::clearArrays() {
    std::vector<glm::vec3>().swap(vertices);
    std::vector<glm::vec3>().swap(normals);
    std::vector<unsigned int>().swap(indices);
}

void PrimitiveMesh::addIndices(unsigned int i1, unsigned int i2, 
        unsigned int i3) {
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}

void PrimitiveMesh::loadToBuffer() {
    buildInterleavedVertices();
    buffersManager.load(interleavedVertices, indices);
}

void PrimitiveMesh::draw(const Shader &shader) {
    buffersManager.draw(shader, material);
}
