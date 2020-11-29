#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <primitiveMesh.hpp>
#include <material.hpp>

class Cylinder : public PrimitiveMesh {
    public:
        Cylinder(float, float, float, int, int, const Material &);

    private:
        //object properties
        float baseRadius;
        float topRadius;
        float height;
        int sectorCount; //# of slices                  
        int stackCount;  //# of stacks

        //auxialiary to build vertices
        std::vector<float> unitCircleVertices;

        void buildVertices();
        void buildUnitCircleVertices();
        std::vector<float> getSideNormals();
};

#endif //!CYLINDER_HPP