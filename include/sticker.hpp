#ifndef STICKER_HPP
#define STICKER_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <circle.hpp>
#include <square.hpp>

#include <shader.h>
#include <material.hpp>

class Sticker {
    public:
        Sticker(float, float, const Material &);
        void scale(glm::vec3);
        void translate(glm::vec3);
        void rotate(glm::vec3, float);

        void loadToBuffer();
        void draw(const Shader &);

        void mapTexCoordToLocation(int);

    private:
        std::vector<Circle> corners;
        std::vector<Square> body;
        glm::vec3 color;

        void mapTexCoordCorners(Circle &, float, int);
        void mapTexCoordBody(Square &, float, float, int);
        void mapTexCoordToLocationAux(Circle &, int);
        void mapTexCoordToLocationAux(Square &, int);
        
};

#endif //!STICKER_HPP