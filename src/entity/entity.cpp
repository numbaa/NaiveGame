#include "entity.h"
#include "../graphics/camera.h"
#include "../scene/physicalspace.h"
#include "../graphics/graphics.h"

//假的update()，没有分开控制physics和graphics的帧率
void Entity::update(shared_ptr<PhysicalSpace> space)
{
    input_->update();
    physics_->update(input_, space);
}
void Entity::update(shared_ptr<Camera> camera)
{
    graphics_->update(physics_, camera);
}

Entity::Entity(shared_ptr<Input> input, shared_ptr<Physics> physics, shared_ptr<Graphics> graphics)
    : input_(input), physics_(physics), graphics_(graphics)
{
}
