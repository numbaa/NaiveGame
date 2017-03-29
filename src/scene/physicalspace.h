#ifndef PHYSICAL_SPACE_H_
#define PHYSICAL_SPACE_H_
#include "stdincs.h"

/*
 * 这个类我没想好具体怎么实现。
 * 初步设想是网格化整个平面空间，整个空间是由很多个小格子组成的
 * 二维数组。每个小格子记录自己属于哪个entity，自己的物理属性，
 * 譬如是否透明，是否参与碰撞检测，等等。
 */
class PhysicalSpace {
};

#endif //ifndef PHYSICAL_SPACE_H_
