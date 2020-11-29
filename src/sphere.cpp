#include <sphere.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <math.h>

Sphere::Sphere(float radius, int sectors, int stacks, const Material &material) :
        PrimitiveMesh(material), radius(radius), sectorCount(sectors),
        stackCount(stacks) {
    buildVertices();
}

void Sphere::buildVertices() {
    const float PI = acos(-1);
    clearArrays();

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    float lengthInv = 1.0f / radius; // normal

    for(int i = 0; i <= stackCount; ++i) {
        stackAngle = PI / 2 - i * stackStep;   // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);  // r * cos(u)
        float z = radius * sinf(stackAngle);   // r * sin(u)

        for(int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;      // starting from 0 to 2pi

            // vertex position
            float x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
            float y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
            vertices.push_back(glm::vec3(x, y, z));

            // normalized vertex normal
            float nx = x * lengthInv;
            float ny = y * lengthInv;
            float nz = z * lengthInv;
            normals.push_back(glm::vec3(nx, ny, nz));

            // tex coord
            float s = (float)j / sectorCount;
            float t = (float)i / stackCount;
            texCoord.push_back(glm::vec2(s, t));
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0) {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }
            if(i != (stackCount-1)) {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }
        }
    }
}
