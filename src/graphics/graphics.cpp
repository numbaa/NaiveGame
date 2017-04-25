#include "graphics.h"

void Graphics::update(shared_ptr<Physics> physics, shared_ptr<Camera> camera)
{
    sprite_->blit(physics, camera);
}
/*
void PlayerGraphics::update(shared_ptr<Physics> physics, shared_ptr<Camera> camaer)
{
}
*/

void SkillGraphics::update(shared_ptr<Physics> physics,shared_ptr<Camera> camera)
{
    static uint32_t last_frames = 0; //持续时间
    last_frames ++;
    if(last_frames > alive_frames_)
        return ;
    //...
}
