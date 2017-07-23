#ifndef PHYSICAL_SPACE_H_
#define PHYSICAL_SPACE_H_
#include "../misc/stdincs.h"
#include <vector>
#include <iostream>
#include <map>
#include <set>
using std::shared_ptr;

/*
 * 这个类我没想好具体怎么实现。
 * 初步设想是网格化整个平面空间，整个空间是由很多个小格子组成的
 * 二维数组。每个小格子记录自己属于哪个entity，自己的物理属性，
 * 譬如是否透明，是否参与碰撞检测，等等。
 */
class Entity;   //头文件里没有用到Entity的函数和属性，只需要一个声明
class Model;
struct collsnRes {
    bool res_; //true false
    int harms_;
    //dx,dy
    collsnRes(bool res = false,int harms = 0)
        :res_(res),harms_(harms) {}
};
//为了解决"由裸指针制作的shared_ptr<>引用计数到0导致的非必要内存释放"
//目的是代替 "delete释放内存",转为什么都不做
//暂时不控制权限
class FakeEntityDelete{
public:
    void operator() (Entity* p)
    {
        (void) p;  
        return ;
    }
};
class PhysicalSpace {

    struct Block {
        Block()
           :bp_(BlockProp(false,0)) {} ;  //默认可穿透
        //Block (const Block& block);             //合成的应该没毛病
        //Block& operator = (const Block& block); //合成的应该没毛病
        BlockProp bp_;
        std::set< shared_ptr<Entity> > owners_; 
    };

    using Grid = std::vector<std::vector<Block>>;
    using ModelPool = std::map<shared_ptr<Model>, shared_ptr<Entity>>;
public:
    PhysicalSpace(uint32_t width, uint32_t height);
    bool addGrid(shared_ptr<Entity> entity);
    bool delGrid(shared_ptr<Entity> entity);
    shared_ptr<Entity> delGrid(Entity* pEntity);
    void clearGrid(uint32_t x,uint32_t y);
    void addModel(shared_ptr<Entity> entity);
    void delModel(shared_ptr<Entity> entity);
    void moveModel(Entity* entity,uint32_t x,uint32_t y);
    void updateModel(shared_ptr<Entity>entity,uint32_t x,uint32_t y);
    collsnRes collision(shared_ptr<Model> model, int32_t x, int32_t y);
    bool isOutOfRang(shared_ptr<Model>model,uint32_t x,uint32_t y);
    std::set<shared_ptr<Entity>> getOwners(uint32_t row,uint32_t col);
private:
    uint32_t    width_;
    uint32_t    height_;
    Grid        grid_;
    ModelPool   mp_;
};

#endif //ifndef PHYSICAL_SPACE_H_
