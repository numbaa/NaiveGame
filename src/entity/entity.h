#ifndef ENTITY_H_
#define ENTITY_H_
#include "../misc/stdincs.h"
#include "../input/input.h"
#include "../graphics/graphics.h"
#include "../physics/physics.h"
#include "../scene/physicalspace.h"
#include "../graphics/camera.h"
using std::shared_ptr;
using std::unique_ptr;

/* Entity类可以理解为 GameObject，玩家、怪物、墙、“回血区域”都是Entity，
 * 玩家和怪物是可以被杀死的，墙和“区域”是无敌的，玩家和区域重叠时产生
 * 特殊效果，如回血。
 * 从物理上看，玩家、怪物、墙之间会产生collision（碰撞），即他们之间不可
 * 重叠。区域是可穿越的。
 */
class Entity {
public:
    Entity(shared_ptr<Input> input, shared_ptr<Physics> physics, shared_ptr<Graphics> graphics);
    void update(shared_ptr<PhysicalSpace> space, shared_ptr<Camera> camera);
    void setHealth(int32_t health);
    uint32_t getHealth() const;
    //...
protected:
    shared_ptr<Input>       input_;
    shared_ptr<Physics>     physics_;
    shared_ptr<Graphics>    graphics_;
    uint32_t                health_;
    //...
};

/* update()的初步设想
 * PhysicalSpace由Scene管理，Camera由Game管理，所以update()时显式传入
 * void Entity::update(shared_ptr<PhysicalSpace> space, shared_ptr<Camera> camera)
 * {
 *      input_->update();
 *      physics_->update(this, space);
 *      graphics_->update(this, camera);
 * }
 */
#endif //ifndef ENTITY_H_
