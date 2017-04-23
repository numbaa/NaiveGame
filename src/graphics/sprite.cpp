#include "sprite.h"
#include "../physics/physics.h"

//这是一个假的Sprite，为了看效果，我把Sprite暂时写成一个不会变化的图

Sprite::Sprite(std::string filename)
    : sf_(filename)
{
}

void Sprite::blit(std::shared_ptr<Physics> phy, shared_ptr<Camera> camera)
{
    sf_.blit(camera->pre_screen_, phy->getPos_x(), phy->getPos_y());
}
