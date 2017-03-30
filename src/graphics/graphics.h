#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "../misc/stdincs.h"
#include "../physics/physics.h"
#include "../graphics/camera.h"
#include "../entity/entity.h"
using std::shared_ptr;

/* Graphics和Physics高度关联，画的东西几乎都要从Physics读取
 * Graphics实在Camera上画东西的，所以要把Camera传进来
 * 有个问题是，Graphics只读取不修改数据，所以physics这些应该应该为const，
 * 然后我就不是很确定语法上怎么搞？
 */
class Graphics {
public:
    Graphics(shared_ptr<Physics> physics) : physics_(physics) {}
    virtual void update(Entity* entity, shared_ptr<Camera> camera);
private:
    shared_ptr<Physics>     physics_;
};

#endif //ifndef GRAPHICS_H_
