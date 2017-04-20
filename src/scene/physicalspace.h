#ifndef PHYSICAL_SPACE_H_
#define PHYSICAL_SPACE_H_
#include "../misc/stdincs.h"
//#include "../entity/entity.h" //解决循环include问题
using std::shared_ptr;

/*
 * 这个类我没想好具体怎么实现。
 * 初步设想是网格化整个平面空间，整个空间是由很多个小格子组成的
 * 二维数组。每个小格子记录自己属于哪个entity，自己的物理属性，
 * 譬如是否透明，是否参与碰撞检测，等等。
 */
class Entity;   //头文件里没有用到Entity的函数和属性，只需要一个声明

const uint32_t BLOCK_SIZE = 12;     //每个Block大小为12*12，12这个数是暂时乱写上去的

class Block {
    Block();
};
class PhysicalSpace {
public:
    PhysicalSpace(int32_t width, int32_t height);
    void addModel(shared_ptr<Entity> entity);
    void delModel(shared_ptr<Entity> entity);
private:
    int32_t width_;
    int32_t height_;
};

#endif //ifndef PHYSICAL_SPACE_H_
