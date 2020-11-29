#ifndef RUBIKS_CUBE_VIEW_HPP
#define RUBIKS_CUBE_VIEW_HPP

#include <vector>

#include <transformCube.hpp>
#include <arcball.hpp>
#include <cubieView.hpp>

#include <shader.h>

class RubiksCubeView {
    public:
        RubiksCubeView(int, int, const std::vector<Material> &);
        void updateScale(double);

        void loadToBuffer();
        void draw(const Shader &);

        TransformCube transformCube;
    private:
        std::vector<CubieView> cubies;
        void initCubies(const std::vector<Material> &);
};

#endif //RUBIKS_CUBE_VIEW_HPP