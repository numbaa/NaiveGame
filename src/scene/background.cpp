#include "background.h"
Background::Background(std::string filename)
    : surface_(filename)
{
}

void Background::blit(int16_t x, int16_t y, uint16_t width, uint16_t height, Camera& camera)
{
    surface_.sub_blit(x, y, width, height, camera.screen_, 0, 0);
}
