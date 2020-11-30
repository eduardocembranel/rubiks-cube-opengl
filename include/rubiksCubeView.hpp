#ifndef RUBIKS_CUBE_VIEW_HPP
#define RUBIKS_CUBE_VIEW_HPP

#include <vector>
#include <memory>

#include <transformCube.hpp>
#include <arcball.hpp>
#include <cubieView.hpp>

#include <shader.h>
#include <cubeRotateManager.hpp>

class RubiksCubeView {
    public:
        RubiksCubeView(int, int, const std::vector<Material> &);

        void rotateFace(int, int);
        void updateFaces(int, int);
        void updateModels(int, int);
        void updateModels2(int, int, float);
        
        void updateScale(double);

        void loadToBuffer();
        void draw(const Shader &);

        TransformCube transformCube;

        CubeRotateManager rotManager;
    private:
        //hold pointer to all the 26 cubies
        std::vector<std::shared_ptr<CubieView>> cubies;

        //struct to face
        struct Face {
            std::vector<std::shared_ptr<CubieView>> cubies;
            std::shared_ptr<Face> westFace;
            std::shared_ptr<Face> eastFace;
            std::shared_ptr<Face> northFace;
            std::shared_ptr<Face> southFace;
        };

        //hold the six faces
        std::vector<std::shared_ptr<Face>> faces;

        void initCubies(const std::vector<Material> &);
        void initFaces();
};

#endif //RUBIKS_CUBE_VIEW_HPP