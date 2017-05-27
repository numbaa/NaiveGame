#include "physicalspace.h"
#include "../entity/entity.h"

PhysicalSpace::PhysicalSpace(uint32_t width, uint32_t height)
    : width_(valid(width)), height_(valid(height)), grid_(height_, std::vector<Block>(width_, Block()))
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

void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    mp_[ entity->getModel() ] = entity;
    int32_t x = entity->getX() / BLOCK_SIZE;
    int32_t y = entity->getY() / BLOCK_SIZE;
    for (auto& p : entity->getModel()->pos)
    {
        grid_[y+p.y][x+p.x] = Block();
        grid_[y+p.y][x+p.x].solid = true;
        grid_[y+p.y][x+p.x].owner = entity;
    }
}

void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    int32_t x = entity->getX() / BLOCK_SIZE;
    int32_t y = entity->getY() / BLOCK_SIZE;
    for (auto& p : entity->getModel()->pos)
    {
        grid_[y+p.y][x+p.x].owner.reset();
        grid_[y+p.y][x+p.x] = Block();
    }
    ModelPool::iterator it = mp_.find( entity->getModel() );
    mp_.erase(it);
}

//collision()检测：当该Model位移(movement_x, movement_y)时，是否与场景内其它物体碰撞
//是返回true，否返回false
//该函数修修补补改了好几遍，逻辑写得有些混乱，日后需要重写
bool PhysicalSpace::collision(shared_ptr<Model> model, int32_t movement_x, int32_t movement_y)
{
    int32_t mx = movement_x / BLOCK_SIZE;
    int32_t my = movement_y / BLOCK_SIZE;
    for (auto& p : model->pos)
    {
        //如果没有下面这个if语句，小人走到上边界和下边界程序会崩溃，
        //原因是下面的 Block& bk = grid_[my+p.y][mx+p.x] 越界了
        if (my+p.y >= height_|| mx+p.x >= width_)
        {
            return true;
        }
        Block& bk = grid_[my+p.y][mx+p.x];
        if (bk.owner != mp_[model] && bk.solid == true)
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
    std::cout<<"Block::operator=: "<<owner.get()<<std::endl;
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
