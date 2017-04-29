#include "entity.h"
#include "../graphics/camera.h"
#include "../scene/physicalspace.h"
#include "../graphics/graphics.h"

void Entity::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    physics_->update(space);
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
Person::Person(shared_ptr<Physics>physics,shared_ptr<Graphics>graphics)
     :Entity(physics,graphics) 
{
}

void Person ::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    physics_->update(space);
}

void Person::updateImage(shared_ptr<Camera> camera)
{
    graphics_->update(physics_,camera);
}

//skill 类
Skill::Skill(shared_ptr<Physics>physics,shared_ptr<Graphics> graphics)
    :Entity(physics,graphics)
{
}

void Skill::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    physics_->update(space);
} 
void Skill::updateImage(shared_ptr<Camera> camera)
{
    graphics_->update(physics_,camera);
}
