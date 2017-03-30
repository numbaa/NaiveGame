#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "../misc/stdincs.h"
#include "../input/input.h"
#include "../entity/entity.h"
#include "../scene/physicalspace.h"
using std::shared_ptr;

/* 一个Physics对象是Entity的一个Component，Entity本身只记录一个简单座标(x, y)，
 * Entity占用的具体空间需由Physics记录，除此之外，Physics还应记录所属Entity的
 * 一些物理特性。
 * update()时，Physics从相应的Input读取一个Command序列，依次执行。并且根据执行
 * 情况，更改自身状态、更改所属PhysicalSapce状态。
 */
class Physics {
public:
    Physics(shared_ptr<Input> input) : input_(input) {}
    virtual void update(Entity* entity, shared_ptr<PhysicalSpace> space) = 0;
private:
    shared_ptr<Input>   input_;
};

#endif //PHYSICS_H_
