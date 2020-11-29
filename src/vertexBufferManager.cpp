#include <vertexBufferManager.hpp>

#include <iostream>

VertexBufferManager::VertexBufferManager() : vao(0), vbo(0), ebo(0),
        indicesCount(0) {

}

void VertexBufferManager::load(const std::vector<float> &interleavedVertices, 
        const std::vector<unsigned int> &indices) {
    if (!vao) {
        genBuffers();
    }
    indicesCount = indices.size();
    bindBuffers();
    setBuffersData(interleavedVertices, indices);
    setVertexAttribs();
}

void VertexBufferManager::genBuffers() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void VertexBufferManager::bindBuffers() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void VertexBufferManager::setBuffersData(
        const std::vector<float> &interleavedVertices, 
        const std::vector<unsigned int> &indices) {
    glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(float), 
            &interleavedVertices[0], GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), 
            &indices[0], GL_STATIC_DRAW);
}

void VertexBufferManager::setVertexAttribs() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
            (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
            (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void VertexBufferManager::draw(const Shader &shader, const Material &material) {
    bindBuffers();

    shader.use();
    shader.setVec3("material.ambient", material.ambient);
    shader.setVec3("material.diffuse", material.diffuse);
    shader.setVec3("material.specular", material.specular);
    shader.setFloat("material.shininess", material.shininess);
    
    if (!material.texture) {
        shader.setBool("material.hasTexture", false);
    } else {
        material.texture->bind(0);
        shader.setInt("material.diffuseTexture", 0);
        shader.setBool("material.hasTexture", true);
    }

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}
