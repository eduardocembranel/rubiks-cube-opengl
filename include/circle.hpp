#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <primitiveMesh.hpp>
#include <material.hpp>

class Circle : public PrimitiveMesh {
    public:
        Circle(float, int, const Material &);

    private:
        //object properties
        float radius;
        int sectorCount;

        //auxiliary to build vertices
        std::vector<float> unitCircleVertices;

        void buildVertices();
        void buildUnitCircleVertices();
};

#endif //!CIRCLE_HPP