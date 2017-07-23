#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "../misc/stdincs.h"
#include "sprite.h"

using std::shared_ptr;
using std::unique_ptr;
using std::string;
/* Graphics和Physics高度关联，画的东西几乎都要从Physics读取
 * Graphics实在Camera上画东西的，所以要把Camera传进来
 * 有个问题是，Graphics只读取不修改数据，所以physics这些应该应该为const，
 * 然后我就不是很确定语法上怎么搞？
 */
class Physics;

class Graphics {
public:
    Graphics(string name,shared_ptr<Sprite>sprite) : name_(name),sprite_(sprite) {}
    virtual ~Graphics() = default;
    virtual void update(shared_ptr<Physics> physics, shared_ptr<Camera> camera);
protected:
    string name_;
    shared_ptr<Sprite>      sprite_;
};


//现在这个PlayerGraphics跟Graphics一模一样，因为我现在只想让程序跑起来
class PlayerGraphics : public Graphics {
public:
    PlayerGraphics(string name,shared_ptr<Sprite>sprite) : Graphics(name,sprite) {}
    virtual void update(shared_ptr<Physics> physics, shared_ptr<Camera> camera);
private:
};

class SkillGraphics : public Graphics {
public:
    SkillGraphics(string name,shared_ptr<Sprite>sprite) 
        :Graphics(name,sprite) {} 
    void update(shared_ptr<Physics> physics,shared_ptr<Camera> camera);
private:
    //uint32_t alive_frames_; //生存时间
};

#endif //ifndef GRAPHICS_H_
