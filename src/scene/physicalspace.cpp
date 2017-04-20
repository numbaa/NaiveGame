#include "physicalspace.h"
#include "../entity/entity.h"

PhysicalSpace::PhysicalSpace(int32_t width, int32_t height)
    : width_(width), height_(height)
{
}

void PhysicalSpace::addModel(shared_ptr<Entity> entity)
{
    return;
}

void PhysicalSpace::delModel(shared_ptr<Entity> entity)
{
    return;
}
