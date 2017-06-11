#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "../misc/stdincs.h"
#include "../input/input.h"
//#include "../entity/entity.h"
#include "../scene/physicalspace.h"
#include "model.h"
using std::shared_ptr;
using std::string;

class Scene;
/* 一个Physics对象是Entity的一个Component，Entity本身只记录一个简单座标(x, y)，
 * Entity占用的具体空间需由Physics记录，除此之外，Physics还应记录所属Entity的
 * 一些物理特性。
 * update()时，Physics从相应的Input读取一个Command序列，依次执行。并且根据执行
 * 情况，更改自身状态、更改所属PhysicalSapce状态。
 */
class Physics {
public:
    enum class Life { Alive, ToKill, Dead };

    Physics(uint32_t x, uint32_t y, shared_ptr<Model> model);
    virtual void update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space);
    virtual ~Physics() = default;

    void setSpeed_x(uint32_t speed) { speed_x_ = speed;}
    void setSpeed_y(uint32_t speed) { speed_y_ = speed;}
    uint32_t getSpeed_x() const { return speed_x_; }
    uint32_t getSpeed_y() const { return speed_y_; }
    //画图的时候可能需要使用这些函数
    uint32_t getPos_x(void) const { return x_;}
    uint32_t getPos_y(void) const { return y_;}
    void setPos_x(uint32_t x) { x_ = x; }
    void setPos_y(uint32_t y) { y_ = y; }
    //Model不应该只是矩形，也就是不应该只有长和宽
    //所以未来下面这几个函数很可能要抛弃
    uint32_t getWidth() const { return model_->getWidth(); }
    uint32_t getHeight() const { return model_->getHeight(); }
    void setWidth(uint32_t width) { model_->setWidth(width); }
    void setHeight(uint32_t height) { model_->setHeight(height); }
    void suicide() { status_ = Life::ToKill; }
    //ugly
    shared_ptr<Model> getModel() { return model_; }
protected:
    uint32_t x_;
    uint32_t y_;
    uint32_t speed_x_;  
    uint32_t speed_y_;  
    shared_ptr<Model>    model_;
    Life                 status_;
    void posUpdate(shared_ptr<PhysicalSpace> space);
};
//需要等到PhysicalSpace实现后，再等进一步实现
class PlayerPhysics : public Physics {
public:
    PlayerPhysics(uint32_t x, uint32_t y, shared_ptr<Model> model);
    void update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space) override;
    void setMoveStep_x(uint32_t step) { move_step_x_ = step;}
    void setMoveStep_y(uint32_t step) { move_step_y_ = step;}
    DIR getDir() const { return dir_cur_;}
    uint32_t getHealthy(void) const { return healthy_;}
    void setHealthy(uint32_t healthy) { healthy_ = healthy; } 
    //...
private:
    void infoUpdate_MOVE_ON(keyvalue_t);
    void infoUpdate_MOVE_OFF(keyvalue_t);
    void infoUpdate_SKILL_ON(keyvalue_t);
    void skill_Q();
    //void infoUpdate_SKILL_OFF(PlayerPhysics&,keyvalue_t);
    PlayerInput input_;
    uint32_t move_step_x_;
    uint32_t move_step_y_;
    DIR dir_cur_;
    int32_t healthy_;
};

class NpcPhysics: public Physics{   //目前跟PlayerPhysics完全一样,先空着
};

class SkillPhysics:public Physics {
public:
    SkillPhysics(uint32_t x, uint32_t y,shared_ptr<Model> model);
    void update(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space) override; 
private:
    int32_t harms_;
};
//...
#endif //PHYSICS_H_
