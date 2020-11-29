#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <primitiveMesh.hpp>
#include <material.hpp>

class Sphere : public PrimitiveMesh {
    public:
        Sphere(float, int, int, const Material &);

    private:
        //object properties
        float radius;
        int sectorCount; // # of slices
        int stackCount;  // # of stacks

        void buildVertices();
};

#endif //!SPHERE_HPP
