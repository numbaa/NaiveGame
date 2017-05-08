#include "sprite.h"
#include "../physics/physics.h"

//这是一个假的Sprite，为了看效果，我把Sprite暂时写成一个不会变化的图

Sprite::Sprite(std::string filename)
    : sf_(filename), picture_name_(filename)
{
}

void Sprite::setColorKey(uint8_t r, uint8_t g, uint8_t b)
{
    sf_.setColorKey(r, g, b);
}

void Sprite::blit(std::shared_ptr<Physics> phy, shared_ptr<Camera> camera)
{
    //这里写简单了，phy->getPos_x()得到的x，应该为Sprite所属Entity的中心，
    //如果直接使用这两个值blit到camera上，贴图会往右和往下偏半个身位
    sf_.blit(camera->pre_screen_, phy->getPos_x(), phy->getPos_y());
}

void Sprite::sub_blit(int16_t x, int16_t y, uint16_t w, uint16_t h, shared_ptr<Physics> phy, shared_ptr<Camera> camera)
{
    sf_.sub_blit(x, y, w, h, camera->pre_screen_, phy->getPos_x(), phy->getPos_y());
}

void PersonSprite::blit(shared_ptr<Physics> phy,shared_ptr<Camera>  camera)
{
    static DIR dir_last = dir_up;
    static int32_t step_state = 0;  //一个行走方向四张图，这个变量确定是哪张图
    static int32_t step_frames = 0; //一张图持续 FPStep帧，这个变量确定到了第几帧
    PlayerPhysics* phy_derived = nullptr; 
    if( !(phy_derived = dynamic_cast<PlayerPhysics*> (phy.get())))
    {
        exit(-1);
    }

    PictureSize psize = getPictureSizeByName(picture_name_);
    //下面这个if意思是：如果没有速度，或者刚换方向，就画该方向的第一个图
    if (   (phy->getSpeed_x() == 0 && phy->getSpeed_y() == 0)
        || (dir_last != phy_derived->getDir())
       )
    {
        dir_last = phy_derived->getDir();
        step_state = 0;
        step_frames = 0;
        //int16_t x = (psize.width_ / 4) * step_state;
        int16_t x = step_state;
        int16_t y = (psize.height_ / 4) * dir_last;    //这里我假设一列图从上到下顺序，
                                                        //跟stdincs.h里的 enum DIR一样，下 左 右 上
        //下面这行有问题，pre_screen_是Camera的protected成员，PersonSprite不是friend，不能访问，但父类Sprite可以
        //sf_.sub_blit(x, y, (psize.width_/4), (psize.height_/4), camera->pre_screen_, phy->getPos_x(), phy->getPos_y());
        Sprite::sub_blit(x, y, (psize.width_/4), (psize.height_/4), phy, camera);
    }
    else
    {
        if (step_frames++ > FPStep)
        {
            step_state = (++step_state == 4 ? 0 : step_state); 
            step_frames = 0;
        }
        int16_t x = (psize.width_ / 4) * step_state;
        int16_t y = (psize.height_ / 4) * dir_last;
        Sprite::sub_blit(x, y, (psize.width_/4), (psize.height_/4), phy, camera);
    }
    
}

SkillSprite::SkillSprite(std::string name)
    :Sprite(name),survival_times_(60)
{
    PictureSize psize = getPictureSizeByName(name);
    image_row_ = psize.row_;
    image_col_ = psize.col_;
    width_ = psize.width_;
    height_ = psize.height_;
}
void SkillSprite:: blit(shared_ptr<Physics> phy,shared_ptr<Camera> camera) 
{
    static uint32_t last_frames = 0;
    if(survival_times_ <= last_frames)
    {
        //destoryEntity(entity);   
        return ;
    }
    uint32_t interval = survival_times_ / (image_row_ * image_col_);         //每张小图片占有的时间
    uint16_t x = 0,y = 0;

    x = (last_frames / interval) % image_col_ * (width_/image_col_);
    y = (last_frames / interval) / image_col_ * (height_/image_row_);

    Sprite::sub_blit(x ,y,width_/image_col_,height_/image_row_,phy,camera);

    last_frames++;
}
