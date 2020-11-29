#ifndef ARCBALL_HPP
#define ARCBALL_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Arcball {
    public:
        Arcball();
        Arcball(float);
        void rotate(int, int, int, int, int, int);
        void setRadius(float);
        glm::mat4 getRotation() const;
        bool animating;

    private:
        glm::mat4 rotation;
        float radius;

        float toNDC(float, int, int, int);
        float calculateZAxis(float, float);    
};

#endif //!ARCBALL_HPP
