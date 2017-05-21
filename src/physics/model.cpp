#include "model.h"
#include <iostream>

Model::Model()
    : width_(0), height_(0)
{}

Model::Model(uint32_t width, uint32_t height)
    : width_(width), height_(height)
{}

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
    return (left->width_ * left->width_ + left->height_ * left->height_)
            -
           (right->width_ * right->width_ + right->height_ * right->height_);
}
