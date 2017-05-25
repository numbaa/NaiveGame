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

bool PhysicalSpace::collision(shared_ptr<Model> model, int32_t x, int32_t y)
{
    int32_t nx = x / BLOCK_SIZE;
    int32_t ny = y / BLOCK_SIZE;
    for (auto& p : model->pos)
    {
        Block bk = grid_[ny+p.y][nx+p.x];
        if (bk.owner != mp_[model] && bk.solid == true)
        {
            return true;
        }
    }
    return false;
}

PhysicalSpace::Block::Block(const PhysicalSpace::Block& block)
{
    this->solid = block.solid;
    this->harm = block.harm;
    this->owner.reset(block.owner.get());
}
PhysicalSpace::Block& PhysicalSpace::Block::operator=(const PhysicalSpace::Block& block)
{
    this->solid = block.solid; this->harm = block.harm; this->owner.reset(block.owner.get()); return *this;
}

PhysicalSpace::Block::~Block()
{
    if (owner.get() != nullptr)
    {
        this->owner.reset();
        std::cout<<"owner:"<<owner<<std::endl;
    }
    std::cout<<"owner: empty"<<std::endl;
}
