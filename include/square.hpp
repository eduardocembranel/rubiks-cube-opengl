#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <primitiveMesh.hpp>
#include <material.hpp>

class Square : public PrimitiveMesh {
    public:
        Square(float size, const Material &);
    
    private:
        //object properties
        float size;

        void buildVertices();
};

#endif //!SQUARE_HPP
