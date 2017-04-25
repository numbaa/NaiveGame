#include "entity.h"
#include "../graphics/camera.h"
#include "../scene/physicalspace.h"
#include "../graphics/graphics.h"

//假的update()，没有分开控制physics和graphics的帧率
void Entity::updatePhysics(shared_ptr<PhysicalSpace> space)
{
    //input_->update();
    physics_->update(nullptr, space); //既然没有Input,physics就不会受外界影响，全靠它自己的属性进行更新
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
    input_->update();   //因为有Input
    physics_->update(input_,space);//所以需要update
}

void Person::updateImage(shared_ptr<Camera> camera)
{
    graphics_->update(physics_,camera);
}
