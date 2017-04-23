#ifndef SPRITE_H_
#define SPRITE_H_
#include <memory>
#include <string>
//#include "../physics/physics.h"
#include "camera.h"

class Physics;

enum StepState { UP, DOWN, LEFT, RIGHT };

const int32_t FPStep = 10;//多少帧一步

class Sprite {
public:
    Sprite(std::string filename);
    void blit(std::shared_ptr<Physics> phy, shared_ptr<Camera> camera);
private:
    int32_t     frames_;
    StepState   ss_;
    Surface     sf_;
};

/*
Sprite::Sprite(std::string filename)
    : frames_(0), ss_(DOWN), sf_(filename)
{
}
*/

/*
void Sprite::blit(std::shared_ptr<Physics> phy, shared_ptr<Surface> dest) 这个dest是Camera的pre_screen_;
{
    ++frames_;
    //StepState curr = get_direction_from_phy()
    if (curr == ss_)
    {
        if (frames_ >= FPStep)
        {
            //blit同一方向的下一个精灵图
            //可以使用sf_.sub_blig(..., dest,...);
        }
        else
        {
            //blit上一个精灵图
        }
    }
    else if (curr == DOWN) {}
    else if (curr == UP) {}
    else if (curr == LEFT) {}
    else if (curr == RIGHT) {}
}
*/

#endif //ifndef SPRITE_H_
