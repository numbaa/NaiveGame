#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "../misc/stdincs.h"
#include "../physics/physics.h"
#include "../graphics/camera.h"
#include "../entity/entity.h"
#include "sprite.h"
using std::shared_ptr;
using std::unique_ptr;

/* Graphics和Physics高度关联，画的东西几乎都要从Physics读取
 * Graphics实在Camera上画东西的，所以要把Camera传进来
 * 有个问题是，Graphics只读取不修改数据，所以physics这些应该应该为const，
 * 然后我就不是很确定语法上怎么搞？
 */
class Graphics {
public:
    Graphics();
    virtual void update(shared_ptr<Physics> physics, shared_ptr<Camera> camera);
protected:
    unique_ptr<Sprite>      sprite_;
};

class PlayerGraphics : Graphics {
public:
    PlayerGraphics();
    virtual void update(shared_ptr<Physics> physics, shared_ptr<Camera> camera);
};

#endif //ifndef GRAPHICS_H_
