#include "entity.h"
#include "../graphics/camera.h"
#include "../scene/physicalspace.h"
#include "../graphics/graphics.h"

//假的update()，没有分开控制physics和graphics的帧率
void Entity::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    physics_->update(nullptr, space);
}
void Entity::updateImage(shared_ptr<Camera> camera)
{
    graphics_->update(physics_, camera);
}

Entity::Entity(shared_ptr<Physics> physics, shared_ptr<Graphics> graphics)
    : physics_(physics), graphics_(graphics)
{
}

//Person 类
void Person ::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    physics_->update(input_,space);
}

void Person::updateImage(shared_ptr<Camera> camera)
{
    graphics_->update(physics_,camera);
}
