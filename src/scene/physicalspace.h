#ifndef PHYSICAL_SPACE_H_
#define PHYSICAL_SPACE_H_
#include "../misc/stdincs.h"
#include <vector>
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

class PhysicalSpace {

    struct Block {
        Block() : solid(false), harm(0), owner(nullptr) {}
        bool                solid;
        uint32_t            harm;
        shared_ptr<Entity>  owner;
    };

    //tricky，因为要实现：
    //  1. 长、宽不是BLOCK_SIZE的倍数不允许构造PhysicalSpace
    //  2. 通过条件1后，用((width / BLOCK_SIZE), (height / BLOCK_SIZE))作为大小初始化grid_这个2维vector
    //就需要像这样使用一个静态函数
    static uint32_t valid(uint32_t value) { if (value % BLOCK_SIZE != 0) std::exit(-1); return value / BLOCK_SIZE; }
    using Grid = std::vector<std::vector<Block>>;
public:
    PhysicalSpace(uint32_t width, uint32_t height);
    void addModel(shared_ptr<Entity> entity);
    void delModel(shared_ptr<Entity> entity);
private:
    uint32_t width_;
    uint32_t height_;
    Grid     grid_;
};

#endif //ifndef PHYSICAL_SPACE_H_
