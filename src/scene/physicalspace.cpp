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

//要实现addModel()就需要改动Entity，在里面建一个存储model数据的变量，
//应该设计一个新的class作为这个变量的类型
void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    return;
}

void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    return;
}
