#ifndef CAMERA_H_
#define CAMERA_H_
#include "../surface/surface.h"

class Camera {
public:
    Camera(int16_t width, int16_t height);
private:
    Surface screen_;
    Surface pre_screen_;
};

#endif //ifndef CAMERA_H_
