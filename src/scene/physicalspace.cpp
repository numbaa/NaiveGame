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
bool PhysicalSpace::addGrid(shared_ptr<Entity> entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    for( auto& p : entity->getModel()->pos)
    {
        //uint32_t row = (y + p.y ) / BLOCK_SIZE;
        //uint32_t col = (x + p.x ) / BLOCK_SIZE; 
        uint32_t row = y / BLOCK_SIZE + p.y;
        uint32_t col = x / BLOCK_SIZE + p.x;
        if(row > height_ || col > width_)  
        {
            exit(-1);
        }
        auto& thisBlock = grid_[row][col];
        auto entityBlockProp = entity->getBlockProp();
        thisBlock.owners_.insert(entity); 
        thisBlock.bp_.harm_ += entityBlockProp.harm_;
        if(thisBlock.bp_.solid_!= true)
        {
            thisBlock.bp_.solid_ = entityBlockProp.solid_;
        }
    }
    return true;
}
//在grid中删除关于entity的信息
bool PhysicalSpace::delGrid(shared_ptr<Entity> entity)
{
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());
    for (auto& p : entity->getModel()->pos)
    {
        uint32_t row = y / BLOCK_SIZE + p.y;
        uint32_t col = x / BLOCK_SIZE + p.x;

        auto& thisBlock = grid_[row][col];
        BlockProp entityBlockProp = entity->getBlockProp();

        auto owner = thisBlock.owners_.find(entity);
        if(owner == thisBlock.owners_.end())
        {
            exit(-1);
        }
        if( thisBlock.owners_.erase(*owner))  //有这个entity
        {
            thisBlock.bp_.harm_ -= entityBlockProp.harm_;
            if(thisBlock.bp_.solid_ == true && entityBlockProp.solid_ == true)
            {
               thisBlock.bp_.solid_ = false;
            }
        }
        else
        {
            exit(-1);
        }

    }
    return true;
}
//"在Entity中引入 owner_,有很多便利，却带来
//很多安全隐患“,比如 shared_ptr<Entity> ptr(owner_) 和
//真正的shared_ptr<Entity> entity 之间有区别，虽然 ptr == entity
//但是 ptr的引用计数是1
//这个重载把版本就是为了解决上面这个麻烦
//为了给addGrid提供参数,它返回了一个真正的entity智能指针
shared_ptr<Entity> PhysicalSpace::delGrid(Entity* entity)
{
    shared_ptr<Entity> realSrc = nullptr;
    shared_ptr<Entity> fakeSrc (entity,FakeEntityDelete());
    int32_t x = static_cast<int32_t>(entity->getX());
    int32_t y = static_cast<int32_t>(entity->getY());

    for (auto& p : entity->getModel()->pos)
    {
        uint32_t row = y / BLOCK_SIZE + p.y;
        uint32_t col = x / BLOCK_SIZE + p.x;

        auto& thisBlock = grid_[row][col];
        BlockProp entityBlockProp = entity->getBlockProp();

        auto owner = thisBlock.owners_.find(fakeSrc);
        if(owner == thisBlock.owners_.end())
        {
            std::cout<<"can not find,owners"<<std::endl;
            exit(-1);
        }
        if(realSrc == nullptr)
        {
            realSrc = *owner;
        }
        if( thisBlock.owners_.erase(*owner))  //有这个entity
        {
            thisBlock.bp_.harm_ -= entityBlockProp.harm_;
            if(thisBlock.bp_.solid_ == true && entityBlockProp.solid_ == true)
            {
               thisBlock.bp_.solid_ = false;
            }
        }
        else
        {
            std::cout<<"can not erase"<<std::endl;
            exit(-1);
        }
    }
    return realSrc;
}
//MemeTao:我认为ModelPool是多余的
//因为Model可以直接由entity获取
void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    std::cout<<"add a modle,entity:"<<entity.get()<<std::endl;
    assert( mp_.find(entity->getModel()) == mp_.end());
    addGrid(entity);
    mp_[ entity->getModel() ] = entity; 
    std::cout<<"add sucess,entity:"<<entity.get()<<std::endl;
}
//清除grid中的一块区域
void PhysicalSpace::clearGrid(uint32_t x,uint32_t y)
{
    (void) x;
    (void) y;
}
void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    std::cout<<"del Model"<<std::endl;
    assert( mp_.find(entity->getModel()) != mp_.end());
    delGrid(entity);
    ModelPool::iterator it = mp_.find(entity->getModel());
    mp_.erase(it);
}
//移动model到指定坐标
//移动后，会主动更新坐标
void PhysicalSpace::moveModel(Entity* entity,uint32_t x,uint32_t y)
{
    //删除原有grid;
    shared_ptr<Entity> realSrc = delGrid(entity);
    //增加指定位置grid
    entity->setX(x);
    entity->setY(y);
    addGrid(realSrc);
}
//更新entity的model到指定坐标
void PhysicalSpace::updateModel(shared_ptr<Entity> entity,uint32_t x,uint32_t y)
{
    ;
}
//碰撞检测：可能只有Creature才用这个版本
collsnRes PhysicalSpace::collision(shared_ptr<Model>model, int32_t movement_x, int32_t movement_y)
{
    int harm_min = 0;//负的表示 治疗 
    int harm_max = 0;
    for( auto &p : model->pos)
    {
        //uint32_t row = (movement_y + it.y) / BLOCK_SIZE;
        //uint32_t col = (movement_x + it.x) / BLOCK_SIZE; 
        uint32_t row = movement_y / BLOCK_SIZE + p.y;
        uint32_t col = movement_x / BLOCK_SIZE + p.x;

        auto& thisBlock = grid_[row][col];
        shared_ptr<Entity> entity = mp_[model]; 
        if(entity == nullptr)
        {
             exit(-1);
        }
        if(thisBlock.bp_.solid_ == true && thisBlock.owners_.find(entity) == thisBlock.owners_.end() )
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
    
    //综合伤害
    return collsnRes(false,harm_max + harm_min);
}

bool PhysicalSpace::isOutOfRang(shared_ptr<Model> model,uint32_t movement_x,uint32_t movement_y)
{
    for( auto &it : model->pos)
    {
        uint32_t row = movement_y / BLOCK_SIZE + it.y;
        uint32_t col = movement_x / BLOCK_SIZE + it.x; 
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
