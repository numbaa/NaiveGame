#include "surface.h"
#include <iostream>
#include <cassert>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const uint32_t rmask = 0x000000ff;
    const uint32_t gmask = 0x0000ff00;
    const uint32_t bmask = 0x00ff0000;
    const uint32_t amask = 0xff000000;
#else
    const uint32_t rmask = 0x000000ff;
    const uint32_t gmask = 0x0000ff00;
    const uint32_t bmask = 0x00ff0000;
    const uint32_t amask = 0xff000000;
#endif
Surface::Surface(uint16_t width, uint16_t height)
    : surface_(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, BPP, rmask, gmask, bmask, amask), SurfaceDeleter())
{
}

Surface::Surface(std::string picture_file)
    : surface_(nullptr, SurfaceDeleter())
{
    SDL_Surface* loaded = IMG_Load(picture_file.c_str());
    assert(loaded != NULL);
    SDL_Surface* optimizedImage = SDL_DisplayFormat(loaded);
    SDL_FreeSurface(loaded);
    loaded = nullptr;
    assert(optimizedImage != NULL);
    surface_.reset(optimizedImage);
}

void Surface::create(uint16_t width, uint16_t height)
{
    SDL_Surface* new_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, BPP, rmask, gmask, bmask, amask);
    assert(new_surface != NULL);
    surface_.reset(new_surface);
}

void Surface::blit(Surface& dest, int16_t x, int16_t y)
{
    if (surface_.get() == nullptr || dest.surface_.get() == nullptr)
    {
        std::cerr<<"Please initialize the Surface first"<<std::endl;
        return;
    }
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(surface_.get(), NULL, dest.surface_.get(), &offset);
}

void Surface::sub_blit(int16_t src_x, int16_t src_y, uint16_t w, uint16_t h, Surface& dest, int16_t dest_x, int16_t dest_y)
{
    if (surface_.get() == nullptr || dest.surface_.get() == nullptr)
    {
        std::cerr<<"Please initialize the Surface first"<<std::endl;
        return;
    }
    SDL_Rect clip;
    clip.x = src_x;
    clip.y = src_y;
    clip.h = h;
    clip.w = w;

    SDL_Rect offset;
    offset.x = dest_x;
    offset.y = dest_y;

    SDL_BlitSurface(surface_.get(), &clip, dest.surface_.get(), &offset);
}

uint16_t Surface::getWidth() const
{
    return surface_->w;
}

uint16_t Surface::getHeight() const
{
    return surface_->h;
}

void Surface::clear()
{
    SDL_FillRect(surface_.get(), NULL, 0x00000000);
}
