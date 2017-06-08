#include "physics.h"
#include <cassert>
#include "../scene/scene.h"
#include <iostream>

#define STEP_DEFAULT    (2)

class Entity;
shared_ptr<Entity> createSkill(string,uint32_t,uint32_t,int32_t,int32_t);
/*
 * 要变成一个函数
#define posUpdate() \
{\
    x_ += speed_x_;\
    y_ += speed_y_;\
}   
*/
//limit(x_,y_);需要知道屏幕尺寸


void Physics::posUpdate(shared_ptr<PhysicalSpace> space)
{
    int32_t x = x_ + speed_x_;
    int32_t y = y_ + speed_y_;
    if (space->collision(this->getModel(), x, y) == false)
    {
        x_ = x;
        y_ = y;
    }
    //updateModel
}

Physics::Physics(uint32_t x, uint32_t y, shared_ptr<Model> model)
    : x_(x),y_(y),speed_x_(0),speed_y_(0), model_(model)
{}
void Physics::update(shared_ptr<PhysicalSpace> space)
{
    posUpdate(space);
    //...
}
//PlayerInput的构造函数暂时没用参数
PlayerPhysics::PlayerPhysics(uint32_t x, uint32_t y, shared_ptr<Model> model)
    : Physics(x, y, model),move_step_x_(STEP_DEFAULT),move_step_y_(STEP_DEFAULT),dir_cur_(dir_up),healthy_(0)
{
}

void PlayerPhysics::infoUpdate_MOVE_ON(keyvalue_t value)
{
    switch (value)
    {
    case DIR_UP: 
        speed_y_ -= move_step_y_;
        dir_cur_ = dir_up;
        break;
    case DIR_DOWN:
        speed_y_ += move_step_y_;
        dir_cur_ = dir_down;
        break;
    case DIR_LEFT:
        speed_x_ -= move_step_x_;
        dir_cur_ = dir_left;
        break;
    case DIR_RIGHT:
        speed_x_ += move_step_x_; 
        dir_cur_ = dir_right;
        break;
    default:break;
    }
}
void PlayerPhysics::infoUpdate_MOVE_OFF(keyvalue_t value)
{
    switch (value)
    {
    case DIR_UP:
    case DIR_DOWN:
        speed_y_ = 0;  //速度归0,方向保持不变
        break;
    case DIR_LEFT:
    case DIR_RIGHT:
        speed_x_ = 0;
        break;
    default:break;
    } 
} 
void PlayerPhysics::infoUpdate_SKILL_ON(keyvalue_t keyvalue)
{
    switch (keyvalue)
    {
    case SKILL1:
        Scene::getInstance()->addEntity(createSkill(SKILL_1_NAME,x_+20,y_,3,0));
        break;
    default:
        //error();
        break;
    }
}
void PlayerPhysics::update(shared_ptr<PhysicalSpace> space)
{
    shared_ptr <Command> cmd (new Command);
    input_.update();  //先更新input
    while(( cmd = input_.getCommand()) != nullptr)  //取命令
    {
        //cmd = input->getCommand();
        keyvalue_t value = cmd->getValue();
        switch(cmd->getType())
        {
        case MOVE_ON: 
            infoUpdate_MOVE_ON(value);
            break;
        case MOVE_OFF:
            infoUpdate_MOVE_OFF(value);
            break;
        case SKILL_ON:
            infoUpdate_SKILL_ON(value);
            break;
        case SKILL_OFF:
            break;
        default:
            break;
        }
    }
    posUpdate(space);   //更新坐标,暂时只能写到这里
    //...//
}

SkillPhysics::SkillPhysics(uint32_t x, uint32_t y,shared_ptr<Model> model)
    : Physics(x, y, model), harms_(0)
{
}
void SkillPhysics::update(shared_ptr<PhysicalSpace>space)
{
    posUpdate(space);
    //harms_属性等待PhysicalSpace
}
