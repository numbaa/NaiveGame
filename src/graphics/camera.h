#ifndef CAMERA_H_
#define CAMERA_H_
#include "../surface/surface.h"
using std::unique_ptr;

class Camera {
    friend class Sprite;
    friend class Background;
public:
    Camera(int16_t width, int16_t height);
    int16_t getWidth() const { return width_; }
    int16_t getHeight() const { return height_; }
    void refresh();
protected:
    int16_t width_;
    int16_t height_;
    Surface screen_;
    Surface pre_screen_;
};

#endif //ifndef CAMERA_H_
