#include "graphics.h"

void Graphics::update(shared_ptr<Physics> physics, Camera& camera)
{
    sprite_->blit(physics, camera);
}
/*
void PlayerGraphics::update(shared_ptr<Physics> physics, shared_ptr<Camera> camaer)
{
}
*/
