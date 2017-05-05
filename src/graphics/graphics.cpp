#include "graphics.h"

/*Graphics::Graphics(string name) 
    :name_(name)
{
}*/
//memetao: 这个函数的定位到底是什么，我一度想把sprite的update放到这里来 
void Graphics::update(shared_ptr<Physics> physics, shared_ptr<Camera> camera)
{
    sprite_->blit(physics, camera);
}

void PlayerGraphics::update(shared_ptr<Physics> physics, shared_ptr<Camera> camera)
{
    sprite_->blit(physics,camera);
}


void SkillGraphics::update(shared_ptr<Physics> physics,shared_ptr<Camera> camera)
{
    sprite_->blit(physics,camera);
}
