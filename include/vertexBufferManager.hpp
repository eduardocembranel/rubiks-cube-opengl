#ifndef VERTEX_BUFFER_MANAGER
#define VERTEX_BUFFER_MANAGER

#include <vector>

#include <shader.h>
#include <material.hpp>

class VertexBufferManager {
    public:
        VertexBufferManager();
        void load(const std::vector<float> &, const std::vector<unsigned int> &);
        void draw(const Shader &, const Material &);

    private:
        unsigned int vao, vbo, ebo;
        size_t indicesCount;

        void genBuffers();
        void bindBuffers();
        void setBuffersData(const std::vector<float> &, 
                const std::vector<unsigned int> &);
        void setVertexAttribs();
};

#endif //!VERTEX_BUFFER_MANAGER