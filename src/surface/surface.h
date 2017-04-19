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
    friend class Camera;
private:
    //提供给Sprite的接口，把自己一部分当作精灵图绘制在dest上
    //void sub_blit(int16_t x, int16_t y, uint16_t w, uint16_t h, shared_ptr<SDL_Surface> dest, int16_t dest_x, int16_t dest_y);
    void sub_blit(int16_t x, int16_t y, uint16_t w, uint16_t h, Surface& dest, int16_t dest_x, int16_t dest_y);
    Surface() {}
public:
    Surface(uint16_t width, uint16_t height);
    template <typename Deleter=SurfaceDeleter> Surface(SDL_Surface* surface, Deleter deleter) : surface_(surface, deleter()) {}
    Surface(std::string picture_file);

    //把自己blit到dest的(x, y)上
    void blit(Surface& dest, int16_t x, int16_t y);
protected:
    shared_ptr<SDL_Surface>     surface_;
};

#endif //ifndef SURFACE_H_
