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
        grid_[0][i].bp_= BlockProp(); //BlockProp()是默认不可穿透的
        grid_[height_-1][i].bp_ = BlockProp();
    }
    for (uint32_t j=0; j<height_; j++)
    {
        grid_[j][0].bp_ = BlockProp();
        grid_[j][width_-1].bp_ = BlockProp();
    }
}
//在grid增加关于这个entity的信息
bool PhysicalSpace::addGrid(shared_ptr<Entity>& entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    uint32_t row_last = INT_MAX;
    uint32_t col_last = INT_MAX;
    for( auto& p : entity->getModel()->pos)
    {
        //Mark:这里优化了一点
        //测试后发现,100个pos,真正需要写入
        //信息的pos不到10个
        uint32_t row = (y + p.y ) / BLOCK_SIZE;
        uint32_t col = (x + p.x ) / BLOCK_SIZE; 
        if(row != row_last || col != col_last)
        {   
            auto& thisBlock = grid_[row][col];
            auto entityBlockProp = entity->getBlockProp();

            thisBlock.owners_.insert(entity); 
            thisBlock.bp_.harm_ += entityBlockProp.harm_;
            if(thisBlock.bp_.solid_!= true)
            {
                thisBlock.bp_.solid_ = entityBlockProp.solid_;
            }

            row_last = row;
            col_last = col;
        }
    }
    return true;
}
//在grid中删除关于entity的信息
bool PhysicalSpace::delGrid(shared_ptr<Entity>& entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    uint32_t row_last = INT_MAX;
    uint32_t col_last = INT_MAX;

    for (auto& p : entity->getModel()->pos)
    {
        uint32_t row = (y + p.y) /BLOCK_SIZE;
        uint32_t col = (x + p.x) /BLOCK_SIZE;
        if(row != row_last || col != col_last)
        {
            auto& thisBlock = grid_[row][col];
            BlockProp entityBlockProp = entity->getBlockProp();
            thisBlock.owners_.erase(entity);
            thisBlock.bp_.harm_ -= entityBlockProp.harm_;
            if(thisBlock.bp_.solid_ == true && entityBlockProp.solid_ == true)
            {
                thisBlock.bp_.solid_ = false;
            }

            row_last = row;
            col_last = col;
        }
    }
    return true;
}
//MemeTao:我认为ModelPool是多余的
//因为Model可以直接由entity获取
void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    assert( mp_.find(entity->getModel()) == mp_.end());
    addGrid(entity);
    mp_[ entity->getModel() ] = entity; 
}
//清除grid中的一块区域
void PhysicalSpace::clearGrid(uint32_t x,uint32_t y)
{
    (void) x;
    (void) y;
}
void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    assert( mp_.find(entity->getModel()) != mp_.end());
    delGrid(entity);
    ModelPool::iterator it = mp_.find(entity->getModel());
    mp_.erase(it);
}
//移动model到指定坐标
//移动后，会主动更新坐标
void PhysicalSpace::moveModel(shared_ptr<Entity> entity,uint32_t x,uint32_t y)
{
    std::cout<<"x_old:"<<entity->getX()<<" y_old:"<<entity->getY()<<std::endl;
    std::cout<<"x:"<<x<<" y:"<<y<<std::endl;
    //删除原有grid;
    delGrid(entity);
    //增加指定位置grid
    entity->setX(x);
    entity->setY(y);
    addGrid(entity);
}
//更新entity的model到指定坐标
void PhysicalSpace::updateModel(shared_ptr<Entity> entity,uint32_t x,uint32_t y)
{
    moveModel(entity,x,y);
}
//碰撞检测：可能只有Creature才用这个版本
collsnRes PhysicalSpace::collision(shared_ptr<Model>model, int32_t movement_x, int32_t movement_y)
{
    uint32_t row_last = INT_MAX;
    uint32_t col_last = INT_MAX;
    int harm_min = 0;//负的表示 治疗 
    int harm_max = 0;
    for( auto &it : model->pos)
    {
        uint32_t row = (movement_y + it.y) / BLOCK_SIZE;
        uint32_t col = (movement_x + it.x) / BLOCK_SIZE; 
        if(row != row_last || col != col_last)
        {
            row_last = row;
            col_last = col;

            auto& thisBlock = grid_[row][col];
            shared_ptr<Entity> entity = mp_[model];  //如果为Nullptr,说明是Player
            if(thisBlock.bp_.solid_ == true && thisBlock.owners_.find(entity) == thisBlock.owners_.end() && entity != nullptr)
            {
                    return collsnRes(true);
            }
            else 
            {
                //记录最大伤害和最小伤害
                if(thisBlock.bp_.harm_ > harm_max) 
                    harm_max = thisBlock.bp_.harm_;
                if(thisBlock.bp_.harm_ < harm_max) 
                    harm_min = thisBlock.bp_.harm_;
            }
        }
    }
    //综合伤害
    return collsnRes(false,harm_max + harm_min);
}

bool PhysicalSpace::isOutOfRang(shared_ptr<Model> model,uint32_t movement_x,uint32_t movement_y)
{
    for( auto &it : model->pos)
    {
        uint32_t row = (movement_y + it.y) / BLOCK_SIZE;
        uint32_t col = (movement_x + it.x) / BLOCK_SIZE; 
        if(row >= height_ || col >= width_ )
        {
            return true;
        }
    }
    return false;
}
std::set<shared_ptr<Entity>> PhysicalSpace::getOwners(uint32_t row,uint32_t col)
{
    return grid_[row][col].owners_;
}

/*PhysicalSpace::Block::Block(const PhysicalSpace::Block& block)
{
    this->bp_ = block.bp_;
    this->owners.clear();
    this->owners = block.owners;
}*/
