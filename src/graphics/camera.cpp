#include "camera.h"

class CameraDeleter {
public:
    void operator()(SDL_Surface*) { return; }
};

Camera::Camera(int16_t width, int16_t height)
    : pre_screen_(Surface(width, height))
{
    screen_.surface_.reset(SDL_SetVideoMode(width, height, BPP, SDL_SWSURFACE), CameraDeleter());
}
