#ifndef ENTITY_H_
#define ENTITY_H_
#include "../misc/stdincs.h"
//#include "../input/input.h"
//#include "../graphics/graphics.h"
#include "../physics/physics.h"
#include "../scene/physicalspace.h"
#include "../graphics/camera.h"
using std::shared_ptr;
using std::unique_ptr;
using std::string;

const uint32_t UPDATE_GAP = 5;
const uint32_t DRAW_GAP   = 10;

/* Entity类可以理解为 GameObject，玩家、怪物、墙、“回血区域”都是Entity，
 * 玩家和怪物是可以被杀死的，墙和“区域”是无敌的，玩家和区域重叠时产生
 * 特殊效果，如回血。
 * 从物理上看，玩家、怪物、墙之间会产生collision（碰撞），即他们之间不可
 * 重叠。区域是可穿越的。
 */
class Input;
class Graphics;
class Scene;

//memetao:按照目前的情况，Entity都可以不用定义派生类了，
//但是我还是觉得明确点好，索性为所有的"Entity"都显式声明
//个Derived Class出来,即使它可能和Base Class完全一样
class Entity {
public:
    Entity(shared_ptr<Physics> physics, shared_ptr<Graphics> graphics);
    virtual void updatePhysics(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space);
    virtual void updateImage(shared_ptr<Camera> camera);
    virtual ~Entity() = default;
    void setX(uint32_t x) { physics_ -> setPos_x(x); }
    void setY(uint32_t y) { physics_ -> setPos_y(y); }
    uint32_t getX() const { return physics_ -> getPos_x(); }
    uint32_t getY() const { return physics_ -> getPos_y(); }
    //下面这两个函数可能很快会被抛弃
    uint32_t getWidth() const { return physics_->getWidth(); }
    uint32_t getHeight() const { return physics_->getHeight(); }
    //ugly
    shared_ptr<Model> getModel() { return physics_->getModel(); }
    //...
protected:
    shared_ptr<Physics>     physics_;
    shared_ptr<Graphics>    graphics_;
    //...
};

//Person  可以理解为每一个活的东西
class Person : public Entity {
public:
    Person(shared_ptr<Physics>physics,shared_ptr<Graphics>graphics);
    void updatePhysics(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace> space) override;
    void updateImage(shared_ptr<Camera> camera) override;

};

//Skill类
class Skill: public Entity {
public:
    Skill(shared_ptr<Physics>physics,shared_ptr<Graphics> graphics);
    void updatePhysics(shared_ptr<Scene> scene, shared_ptr<PhysicalSpace>space) override;
    void updateImage(shared_ptr<Camera> camera) override;
};

#endif //ifndef ENTITY_H_
