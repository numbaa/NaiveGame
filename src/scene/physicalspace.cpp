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
        grid_[0][j].solid = true;
        grid_[width_-1][j].solid = true;
    }
}

void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    return;
}

void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    return;
}
