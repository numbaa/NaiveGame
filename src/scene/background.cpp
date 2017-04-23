#include "background.h"

Background::Background(std::string filename)
    : surface_(filename)
{
}

void Background::blit(int16_t x, int16_t y, uint16_t width, uint16_t height, Surface& screen)
{
    surface_.sub_blit(x, y, width, height, screen, 0, 0);
}

uint16_t Background::getWidth() const
{
    return surface_.getWidth();
}

uint16_t Background::getHeight() const
{
    return surface_.getHeight();
}
