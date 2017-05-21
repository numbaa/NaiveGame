#include "../misc/stdincs.h"

//简单粗暴的Model类
//它认为世界是方的，由一个个Block组成
//于是它记住了每个物体的长和宽各占多少Block
//
//我设想的Model不应该只是个矩形...
//如果只是矩形就不会大费周章搞Block，先在在PhysicalSpace里使用
//Block可以方便以后完善Model，只是苦了现在要根据Block检查碰撞
class Model {
    friend bool operator<(const std::shared_ptr<Model>& left, const std::shared_ptr<Model>& right);
public:
    Model();
    Model(uint32_t width, uint32_t height);
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    void setWidth(uint32_t width);
    void setHeight(uint32_t height);
private:
    uint32_t     width_;
    uint32_t     height_;
};

//要使用map就要operator<
bool operator<(const std::shared_ptr<Model>& left, const std::shared_ptr<Model>& right);
