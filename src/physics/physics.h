#ifndef PHYSICS_H_
#define PHYSICS_H_
#include "../misc/stdincs.h"
#include "../input/input.h"
//#include "../entity/entity.h"
#include "../scene/physicalspace.h"
using std::shared_ptr;
using std::string;
/* 一个Physics对象是Entity的一个Component，Entity本身只记录一个简单座标(x, y)，
 * Entity占用的具体空间需由Physics记录，除此之外，Physics还应记录所属Entity的
 * 一些物理特性。
 * update()时，Physics从相应的Input读取一个Command序列，依次执行。并且根据执行
 * 情况，更改自身状态、更改所属PhysicalSapce状态。
 */
class Physics {
public:
    Physics();
    virtual void update(shared_ptr<Input> input, shared_ptr<PhysicalSpace> space);
    virtual ~Physics() = default;

    void setSpeed_x(uint32_t speed) { speed_x_ = speed;}
    void setSpeed_y(uint32_t speed) { speed_y_ = speed;}
    //画图的时候可能需要使用这些函数
    uint32_t getPos_x(void) const { return x_;}
    uint32_t getPos_y(void) const { return y_;}
    void setPos_x(uint32_t x) { x_ = x; }
    void setPos_y(uint32_t y) { y_ = y; }
protected:
    uint32_t x_;
    uint32_t y_;
    uint32_t speed_x_;  
    uint32_t speed_y_;  
};
//需要等到PhysicalSpace实现后，再等进一步实现
class PlayerPhysics : public Physics {
public:
    PlayerPhysics();
    void update(shared_ptr<Input> input, shared_ptr<PhysicalSpace> space) override;
    void setMoveStep_x(uint32_t step) { move_step_x_ = step;}
    void setMoveStep_y(uint32_t step) { move_step_y_ = step;}
    DIR getDir() const { return dir_cur_;}
    uint32_t getHealthy(void) const { return healthy_;}
    void setHealthy(uint32_t healthy) { healthy_ = healthy; } 
    //...
private:
    void infoUpdate_MOVE_ON(keyvalue_t);
    void infoUpdate_MOVE_OFF(keyvalue_t);
    //void infoUpdate_SKILL_ON(PlayerPhysics&,keyvalue_t);
    //void infoUpdate_SKILL_OFF(PlayerPhysics&,keyvalue_t);
    uint32_t move_step_x_;
    uint32_t move_step_y_;
    DIR dir_cur_;
    uint32_t healthy_;
};

class NpcPhysics: public Physics{   //目前跟PlayerPhysics完全一样,先空着
};

class SkillPhysics:public Physics {
public:
    SkillPhysics();
    void update(shared_ptr<Input> input,shared_ptr<PhysicalSpace> space) override; 
private:
    string owner_;
    //uint32_t alives_frames_; 
    int32_t harms_;
};
//...
#endif //PHYSICS_H_
