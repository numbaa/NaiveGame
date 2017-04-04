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
    friend class Sprite;
private:
    //提供给Sprite的接口，把自己一部分当作精灵图绘制在dest上
    void sub_blit_to(int16_t x, int16_t y, uint16_t w, uint16_t h, shared_ptr<SDL_Surface> dest, int16_t dest_x, int16_t dest_y);
public:
    Surface(uint16_t width, uint16_t height);
    Surface(std::string picture_file);

    //把source blit到本Surface的（x，y）上
    void blit(int16_t x, int16_t y, shared_ptr<SDL_Surface> source);
private:
    shared_ptr<SDL_Surface>     surface_;
};

#endif //ifndef SURFACE_H_
