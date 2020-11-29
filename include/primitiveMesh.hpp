#ifndef PRIMITIVE_MESH_HPP
#define PRIMITIVE_MESH_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>
#include <vertexBufferManager.hpp>
#include <material.hpp>

class PrimitiveMesh {
    public:
        PrimitiveMesh(const Material &);
        void scale(glm::vec3);
        void translate(glm::vec3);
        void rotate(glm::vec3, float);
        void buildInterleavedVertices();
        const std::vector<float> getInterleavedVertices() const;
        std::vector<float> &getInterleavedVertices();
        std::vector<unsigned int> getIndices() const;

        void loadToBuffer();
        void draw(const Shader &);

        std::vector<glm::vec2> texCoord;

    protected:
        void clearArrays();
        void addIndices(unsigned int, unsigned int, unsigned int);
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;

    private:
        //vertex attributes
        Material material;
        
        //interleaved vertex attributes and indices
        std::vector<float> interleavedVertices;
        std::vector<unsigned int> indices;

        VertexBufferManager buffersManager;

        virtual void buildVertices() = 0;    
};

#endif //!PRIMITIVE_MESH_HPP