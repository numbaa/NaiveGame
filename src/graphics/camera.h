#ifndef CAMERA_H_
#define CAMERA_H_
#include "../surface/surface.h"
using std::unique_ptr;

class Camera {
    friend class Sprite;
public:
    Camera(int16_t width, int16_t height);
    void refresh();
protected:
    int16_t width_;
    int16_t height_;
    Surface screen_;
    Surface pre_screen_;
};

#endif //ifndef CAMERA_H_
