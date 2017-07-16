#include "physicalspace.h"
#include "../entity/entity.h"
#include <cassert>
#include <iostream>


PhysicalSpace::PhysicalSpace(uint32_t width, uint32_t height)
    : width_(promote(width,BLOCK_SIZE)), height_(promote(height,BLOCK_SIZE)), grid_(height_,std::vector<Block>(width_, Block()))
{
    //下面代码用作测试，功能是给地图周围一圈变为“不可逾越”
    for (uint32_t i=0; i<width_; i++)
    {
        grid_[0][i].solid = true;
        grid_[height_-1][i].solid = true;
    }
    for (uint32_t j=0; j<height_; j++)
    {
        grid_[j][0].solid = true;
        grid_[j][width_-1].solid = true;
    }
}
//在grid中填充一块区域
//至于会不会覆盖别人的区域,由调用者负责!
void PhysicalSpace::addGrid(shared_ptr<Entity>& entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    for( auto& p : entity->getModel()->pos)
    {
        //Mark:这里可以优化
        uint32_t row = (y + p.y ) / BLOCK_SIZE;
        uint32_t col = (x + p.x ) / BLOCK_SIZE; 
        grid_[row][col] = Block();
        grid_[row][col].solid = true;
        grid_[row][col].owner = entity;
    }
}

void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    assert( mp_.find(entity->getModel()) == mp_.end());
    addGrid(entity);
    mp_[ entity->getModel() ] = entity; 
}
//清除grid中的一块区域
void PhysicalSpace::clearGrid(shared_ptr<Entity>& entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    for (auto& p : entity->getModel()->pos)
    {
        uint32_t row = (y + p.y) /BLOCK_SIZE;
        uint32_t col = (x + p.x) /BLOCK_SIZE;
        grid_[row][col].owner.reset();
        grid_[row][col] = Block();
    }
}
void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    assert( mp_.find(entity->getModel()) != mp_.end());
    clearGrid(entity);
    ModelPool::iterator it = mp_.find(entity->getModel());
    mp_.erase(it);
}
//移动grid中的一块区域
//在未弄清楚移动细节前,别轻易改动这个函数
void PhysicalSpace::moveGrid(int32_t x_old,int32_t y_old,shared_ptr<Entity>& owner)
{
    const uint32_t x = owner->getX();
    const uint32_t y = owner->getY();
    owner->setX(x_old);
    owner->setY(y_old);
    clearGrid(owner); //清除原有位置的model
    owner->setX(x);   //必须要恢复
    owner->setY(y); 

    addGrid(owner);
}
//collision()检测：当该Model位移(movement_x, movement_y)时，是否与场景内其它物体碰撞
//是返回true，否返回false
//该函数修修补补改了好几遍，逻辑写得有些混乱，日后需要重写
bool PhysicalSpace::collision(shared_ptr<Model> model, int32_t movement_x, int32_t movement_y)
{
    for( auto &it : model->pos)
    {
        uint32_t row = (movement_y + it.y) / BLOCK_SIZE;
        uint32_t col = (movement_x + it.x) / BLOCK_SIZE; 
        if(row >= height_ || col >= width_ )
        {
            return true;
        }
        Block& bk = grid_ [row][col];
        if( bk.owner != mp_[model] && bk.solid == true) 
        {
            return true;
        }
    }
    return false;
}


//下面这三个函数，都是为了修补collision()崩溃而写的，有些帮上了忙，有些则不
PhysicalSpace::Block::Block(const PhysicalSpace::Block& block)
{
    this->solid = block.solid;
    this->harm = block.harm;
    this->owner.reset(block.owner.get());
}
PhysicalSpace::Block& PhysicalSpace::Block::operator=(const PhysicalSpace::Block& block)
{
    this->solid = block.solid;
    this->harm = block.harm;
    //std::cout<<"Block::operator=: "<<owner.get()<<std::endl;
    this->owner.reset(block.owner.get());
    return *this;
}

PhysicalSpace::Block::~Block()
{
    if (owner.get() != nullptr)
    {
        std::cout<<"owner:"<<owner<<std::endl;
        this->owner.reset();
    }
    //std::cout<<"owner: empty"<<std::endl;
}
