#ifndef SURFACE_H_
#define SURFACE_H_
#include "../misc/stdincs.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
using std::shared_ptr;

const int32_t BPP = 32;     //Bit per Pixel

class SurfaceDeleter {
public:
    void operator()(SDL_Surface* sf)
    {
        if (sf == NULL)
            return;
        SDL_FreeSurface(sf);
    }
};

class Surface {
    //我想写成下面这样，可是不行
    //friend void Camera::refresh();
    friend class Camera;
public:
    Surface() : surface_(nullptr) {}
    Surface(uint16_t width, uint16_t height);
    Surface(std::string picture_name);
    template <typename Deleter=SurfaceDeleter> Surface(SDL_Surface* surface, Deleter deleter) : surface_(surface, deleter) {}

    //把自己blit到dest的(x, y)上
    void blit(Surface& dest, int16_t x, int16_t y);
    void sub_blit(int16_t x, int16_t y, uint16_t w, uint16_t h, Surface& dest, int16_t dest_x, int16_t dest_y);
    void clear();
    void create(uint16_t width, uint16_t height);
    uint16_t getHeight() const;
    uint16_t getWidth() const;
    void setColorKey(uint8_t r, uint8_t g, uint8_t b);
    const SDL_PixelFormat* getPixelFormat() const;
protected:
    shared_ptr<SDL_Surface>     surface_;
};

#endif //ifndef SURFACE_H_
