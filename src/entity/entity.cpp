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

shared_ptr<Entity> createSkill(string skillName,
                               uint32_t posx,
                               uint32_t posy,
                               int32_t xspeed, //左边:负   右边:正 
                               int32_t yspeed)
{
    //获取图片信息,初始化model
    PictureSize imageInfo = getPictureSizeByName(skillName); 
    uint32_t blocks_width = imageInfo.num_of_blocks_width_;
    uint32_t blocks_height = imageInfo.num_of_blocks_height_;

    shared_ptr<Model> model(new Model(blocks_width,blocks_height));
    
    shared_ptr<Physics> phy(new SkillPhysics(posx, posy,model));
    phy->setSpeed_x(xspeed);
    phy->setSpeed_y(yspeed);

    shared_ptr<Sprite> sprite(new SkillSprite(skillName));
    shared_ptr<Graphics> grph(new SkillGraphics(skillName,sprite));

    shared_ptr<Entity> skill ( new Skill(phy,grph));
    return skill;
}

