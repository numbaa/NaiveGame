#include "physics.h"
#define STEP_DEFAULT    (10)
#define posUpdate() \
{\
    x_ += speed_x_;\
    y_ += speed_y_;\
}   
//limit(x_,y_);需要知道屏幕尺寸

PlayerPhysics::PlayerPhysics(shared_ptr<Input>input)
    :Physics(input),x_(0),y_(0),speed_x_(0),speed_y_(0),move_step_x_(STEP_DEFAULT),move_step_y_(STEP_DEFAULT),dir_cur_(dir_right)
{
    ;
}
void infoUpdate_MOVE_ON(PlayerPhysics& phy,keyvalue_t value)
{
    switch (value)
    {
    case DIR_UP: 
        phy.speed_y_ -= phy.move_step_y_;
        phy.dir_cur_ = dir_up;
        break;
    case DIR_DOWN:
        phy.speed_y_ += phy.move_step_y_;
        phy.dir_cur_ = dir_down;
        break;
    case DIR_LEFT:
        phy.speed_x_ -= phy.move_step_x_;
        phy.dir_cur_ = dir_left;
        break;
    case DIR_RIGHT:
        phy.speed_x_ += phy.move_step_x_; 
        phy.dir_cur_ = dir_right;
        break;
    default:break;
    }
}
void infoUpdate_MOVE_OFF(PlayerPhysics& phy,keyvalue_t value)
{
    switch (value)
    {
    case DIR_UP:
    case DIR_DOWN:
        phy.speed_y_ = 0;  //速度归0,方向保持不变
        break;
    case DIR_LEFT:
    case DIR_RIGHT:
        phy.speed_x_ = 0;
        break;
    default:break;
    } 
} 
/*void infoUpdate_SKILL_ON(Entity& entity,shared_ptr<PhysicalSpace>& space,PlayerPhysics& phy,keyvalue_t value)
{
    switch(value)
    {
    case SKILL1:
    case SKILL2:
    case SKILL3:
    default:break;
    }
}*/
/*void infoUpdate_SKILL_OFF(Entity& entity,shared_ptr<PhysicalSpace>& space,PlayerPhysics& phy,keyvalue_t value)
{
    switch(value)
    {
    case SKILL1:
    case SKILL2:
    case SKILL3:
    default:break;
    }
}*/
void PlayerPhysics::update(Entity& entity ,shared_ptr<PhysicalSpace>& space)
{
    shared_ptr <Command> cmd (new Command);
    while(cmd != nullptr)  //取命令
    {
        cmd = input_->getCommand();
        keyvalue_t value = cmd->getValue();
        switch(cmd->getType())
        {
        case MOVE_ON: 
            infoUpdate_MOVE_ON(*this,value); //传的是引用
            break;
        case MOVE_OFF:
            infoUpdate_MOVE_OFF(*this,value);
            break;
        case SKILL_ON:
            //infoUpdate_SKILL_ON(entity,space,*this,value);
            break;
        case SKILL_OFF:
            //infoUpdate_SKILL_OFF(entity,space,*this,value);
            break;
        default:
            break;
        }
    }
    posUpdate();   //更新坐标,暂时只能写到这里
    //...//
}
