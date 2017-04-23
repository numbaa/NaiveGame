#ifndef CAMERA_H_
#define CAMERA_H_
#include "../surface/surface.h"
using std::unique_ptr;

class Background;

class Camera {
    friend class Sprite;
    friend class Background;
public:
    Camera(int16_t width, int16_t height);
    int16_t getWidth() const { return width_; }
    int16_t getHeight() const { return height_; }
    void refresh(int16_t x, int16_t y);
    void changeBackground(shared_ptr<Background> bg);
protected:
    int16_t                 width_;
    int16_t                 height_;
    Surface                 screen_;
    Surface                 pre_screen_;
    shared_ptr<Background>  bg_;
};

#endif //ifndef CAMERA_H_
