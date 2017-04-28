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

void PersonSprite::blit(shared_ptr<Physics> phy,shared_ptr<Camera>  camera)
{
    static DIR dir_last = dir_up;
    //static uint32_t pos_x_last = 0,pos_y_last = 0;
    PlayerPhysics* phy_derived = nullptr; 
    if( !(phy_derived = dynamic_cast<PlayerPhysics*> (phy.get())))
    {
        exit(-1);
    }
    if(dir_last != phy_derived->getDir())
    {
        dir_last = phy_derived->getDir();
        //需要知道尺寸 
    }
    
}
