#include "camera.h"
#include "../scene/background.h"

class CameraDeleter {
public:
    void operator()(SDL_Surface*) { return; }
};

Camera::Camera(int16_t width, int16_t height)
    : width_(width), height_(height),
      screen_(SDL_SetVideoMode(width_, height_, BPP, SDL_SWSURFACE), CameraDeleter()),
      pre_screen_(Surface()),
      bg_(nullptr)
{
}

void Camera::changeBackground(shared_ptr<Background> bg)
{
    bg_ = bg;
    pre_screen_.create(bg_->getWidth(), bg_->getHeight());
}

//这也是个假的refresh()，摄像机位置固定不动
//TODO:让摄像机跟随主角动起来
//传进来的(x,y)是主角在整个地图的位置，根据这个位置
//计算sub_blit()前两个参数的值
void Camera::refresh(int16_t x, int16_t y)
{
    bg_->blit(0, 0, width_, height_, screen_);
    pre_screen_.sub_blit(0, 0, width_, height_, screen_, 0, 0);
    SDL_Flip(screen_.surface_.get());
    pre_screen_.clear();
}
