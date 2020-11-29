#ifndef CUBIE_VIEW_HPP
#define CUBIE_VIEW_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sphere.hpp>
#include <cylinder.hpp>
#include <square.hpp>
#include <sticker.hpp>

#include <shader.h>
#include <material.hpp>

class CubieView {
    public:
        CubieView(glm::vec3, glm::vec3, float, const Material &);
        void addSticker(const Material &, const std::string &, int);
        
        void scale(glm::vec3);
        void translate(glm::vec3);
        void rotate(glm::vec3, float);

        void loadToBuffer();
        void draw(const Shader &);

    private:
        std::vector<Cylinder> edges;
        std::vector<Sphere> corners;
        std::vector<Square> faces;
        std::vector<Sticker> stickers;
        glm::vec3 color;
        float size;
};

#endif //!CUBIE_VIEW_HPP