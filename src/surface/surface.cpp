#include "surface.h"
#include <cassert>

Surface::Surface(uint16_t width, uint16_t height)
    : surface_(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, BPP, 0, 0, 0, 0), SurfaceDeleter())
{
}

Surface::Surface()
    : surface_(nullptr, SurfaceDeleter())
{
}

Surface::Surface(std::string picture_file)
    : surface_(nullptr, SurfaceDeleter())
{
    SDL_Surface* loaded = IMG_Load(picture_file.c_str());

    assert(loaded == NULL);

    surface_.reset(SDL_DisplayFormat(loaded));
}

void Surface::blit(int16_t x, int16_t y, shared_ptr<SDL_Surface> src)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src.get(), NULL, surface_.get(), &offset);
}

void Surface::sub_blit(int16_t src_x, int16_t src_y, uint16_t w, uint16_t h, shared_ptr<SDL_Surface> dest, int16_t dest_x, int16_t dest_y)
{
    SDL_Rect clip;
    clip.x = src_x;
    clip.y = src_y;
    clip.h = h;
    clip.w = w;

    SDL_Rect offset;
    offset.x = dest_x;
    offset.y = dest_y;

    SDL_BlitSurface(surface_.get(), &clip, dest.get(), &offset);
}
