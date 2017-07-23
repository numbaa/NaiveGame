#include "physics.h"
#include <cassert>
#include "../scene/scene.h"
#include "../entity/entity.h"
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
    (void) space;
    std::cout<<"Physics::posUpdate() is empty"<<std::endl;
    /*uint32_t x = x_ + speed_x_;
    uint32_t y = y_ + speed_y_;

    collsnRes res = space->collision(this->getModel(), x, y);
    if (res.res_ == false)  //没有阻碍
    {     
        shared_ptr<Entity> entity(owner_); 
        space->updateModel(entity,x,y);
        x_ = x; y_ = y;
    }*/
    //...

}
void PlayerPhysics::posUpdate(shared_ptr<PhysicalSpace> space)
{
    uint32_t x = x_ + speed_x_;
    uint32_t y = y_ + speed_y_;
   
    //即使坐标没有变化,还是得更新,因为 它现在或许就站在Skill范围内 
    //所以应该是持续掉血的
    if(x!=x_)
        std::cout<<"x_"<<x_<<" x:"<<x<<std::endl;
    collsnRes res = space->collision(this->getModel(), x, y);
    if (res.res_ == false)  //没有阻碍
    {     
        shared_ptr<Entity> entity(owner_); 
        healthy_ -= res.harms_;
        space->moveModel(entity,x,y); //会更改坐标
        return ;
    }
    //...
}
void SkillPhysics::posUpdate(shared_ptr<PhysicalSpace> space)
{
    uint32_t x = x_ + speed_x_;
    uint32_t y = y_ + speed_y_;
    if(speed_x_ != 0 && speed_y_ != 0) 
    {
        if( space->isOutOfRang(this->getModel(),x,y) != true)
        {
            return;
        }
    }
    //skill类 不参与碰撞检测
    x_ = x; 
    y_ = y;
    //更改后，SKILL不再主动对Creature伤害,因为实现特别困难
    //转为增加BLOCK的harm记录，间接影响Creature
    
    //对所有路过的entity造成伤害
    //每物理更新一次 就对entities伤害一次
    /*uint32_t row = y_ / BLOCK_SIZE;
    uint32_t col = x_ / BLOCK_SIZE;
    std::set<shared_ptr<Entity>> owners = space->getOwners(row,col);
    for( auto it : owners)
    {
       //harmToEntity(it);
    }*/
    //update model
    shared_ptr<Entity> entity( owner_);
    space->moveModel(entity,x_,y_);
}
Physics::Physics(uint32_t x, uint32_t y, shared_ptr<Model> model,BlockProp bp)
    : x_(x),y_(y),speed_x_(0),speed_y_(0), model_(model),bp_(bp),status_(Life::Alive),owner_ (nullptr)
{}

//感觉这个地方有安全性问题
bool Physics::setOwner(Entity* entity)
{
    if(owner_ != nullptr)
        return false;
    owner_ = entity;
    return true;
}
void Physics::update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space)
{
    if (status_ == Life::ToKill)
    {
        //Modify:我改用你之前的第1个方案
        shared_ptr<Entity> entity(owner_);
        scene->kill(entity);
        status_ = Life::Dead;
        return;
    }
    else if (status_ == Life::Dead)
    {
        return;
    }
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
        skill_Q();
        break;
    default:
        //error();
        break;
    }
}
void PlayerPhysics::update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space)
{
    if (status_ == Life::ToKill)
    {
        shared_ptr<Entity> entity(owner_) ;
        scene->kill(entity);
        status_ = Life::Dead;
        return;
    }
    else if (status_ == Life::Dead)
    {
        return;
    }
    shared_ptr <Command> cmd (new Command);
    input_.update();  //先更新input
    while(( cmd = input_.getCommand()) != nullptr)  //取命令
    {
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
    //更新坐标
    posUpdate(space);   
    //...//
}

SkillPhysics::SkillPhysics(uint32_t x, uint32_t y,shared_ptr<Model> model)
    : Physics(x, y, model), harms_(0)
{
}
void SkillPhysics::update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace>space)
{
    if (status_ == Life::ToKill)
    {
        shared_ptr<Entity> entity(owner_);
        scene->kill(entity);
        status_ = Life::Dead;
        return;
    }
    else if (status_ == Life::Dead)
    {
        return;
    }
    posUpdate(space);
    //harms_属性等待PhysicalSpace
}
void PlayerPhysics::skill_Q()
{
    switch (dir_cur_)
    {
    case DIR::dir_right:
        Scene::getInstance()->addEntity(createSkill(SKILL_1_NAME,x_+20,y_,3,0));
        break;
    case DIR::dir_left:
        Scene::getInstance()->addEntity(createSkill(SKILL_1_NAME, x_-20, y_, -3, 0));
        break;
    case DIR::dir_up:
        Scene::getInstance()->addEntity(createSkill(SKILL_1_NAME, x_, y_-40, 0, -3));
        break;
    case DIR::dir_down:
        Scene::getInstance()->addEntity(createSkill(SKILL_1_NAME, x_, y_+40, 0, 3));
        break;
    }
}
