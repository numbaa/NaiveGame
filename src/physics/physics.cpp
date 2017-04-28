#include "physics.h"
#include <cassert>

#define STEP_DEFAULT    (10)
#define posUpdate() \
{\
    x_ += speed_x_;\
    y_ += speed_y_;\
}   
//limit(x_,y_);需要知道屏幕尺寸



//更新日志: Physics 不再是抽象基类
//space还是没能利用上

Physics::Physics()
    : x_(0),y_(0),speed_x_(0),speed_y_(0)
{}
void Physics::update(shared_ptr<PhysicalSpace> space)
{
    posUpdate();
    //...
}
//PlayerInput的构造函数暂时没用参数
PlayerPhysics::PlayerPhysics()
    : Physics(),move_step_x_(STEP_DEFAULT),move_step_y_(STEP_DEFAULT),dir_cur_(dir_up),healthy_(0)
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
            break;
        case SKILL_OFF:
            break;
        default:
            break;
        }
    }
    posUpdate();   //更新坐标,暂时只能写到这里
    //...//
}

SkillPhysics::SkillPhysics()
    :harms_(0)
{
    ;
}
void SkillPhysics::update(shared_ptr<PhysicalSpace>space)
{
    posUpdate();
    //harms_属性等待PhysicalSpace
}
