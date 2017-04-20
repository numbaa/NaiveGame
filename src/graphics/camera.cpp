#include "camera.h"

class CameraDeleter {
public:
    void operator()(SDL_Surface*) { return; }
};

Camera::Camera(int16_t width, int16_t height)
    : width_(width), height_(height),
      screen_(SDL_SetVideoMode(width_, height_, BPP, SDL_SWSURFACE), CameraDeleter()),
      pre_screen_(Surface(width, height))
{
}

//这也是个假的refresh()，摄像机位置固定不动
void Camera::refresh()
{
    pre_screen_.sub_blit(0, 0, width_, height_, screen_, 0, 0);
}
