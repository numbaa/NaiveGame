#include "model.h"
#include <iostream>

Model::Model(uint32_t width, uint32_t height)
    : width_(width), height_(height)
{
    pos.reserve(width * height);
    std::cout<<"model width:"<<width_<<" height:"<<height_<<std::endl;
    int32_t half_x = width_ / 2;
    int32_t half_y = height_ / 2;
    for (int i=-half_x; i<half_x; i++)
        for (int j=-half_y; j<half_y; j++)
        {
            pos.push_back(Pos(i, j));
        }
}

uint32_t Model::getWidth() const
{
    if (width_ == 0)
    {
        std::cerr<<"Please initialize Model::width_ before using it"<<std::endl;
    }
    return width_;
}

uint32_t Model::getHeight() const
{
    if (height_ == 0)
    {
        std::cerr<<"Please initialize Model::height_ before using it"<<std::endl;
    }
    return height_;
}

void Model::setWidth(uint32_t width)
{
    width_ = width;
}

void Model::setHeight(uint32_t height)
{
    height_ = height;
}

bool operator<(const std::shared_ptr<Model>& left, const std::shared_ptr<Model>& right)
{
    /*return (left->width_ * left->width_ + left->height_ * left->height_)
            -
           (right->width_ * right->width_ + right->height_ * right->height_);*/
    return (left->width_ * left->height_ - right->width_ * right->height_);
}
