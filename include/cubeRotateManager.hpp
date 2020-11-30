#ifndef CUBE_ROTATE_MANAGER_HPP
#define CUBE_ROTATE_MANAGER_HPP

class CubeRotateManager {
    public:
        CubeRotateManager(float);
        void beginRotate(int, int);
        float rotateAnimated();

        bool rotating;
        int face;
        int opt;
        float prevTime;
        float animDuration;
        float totalAngle;
        float accumulatedAngle;
};

#endif //!CUBE_ROTATE_MANAGER_HPP