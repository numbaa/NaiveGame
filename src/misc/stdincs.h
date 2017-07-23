#ifndef STDINCS_H_
#define STDINCS_H_
/*
 * 所谓 stdincs.h，即为 Standard Include Headers
 * 用来包括一些项目组几乎每个文件都会用到的标准头文件
 */

#include <memory>
#include <cstdint>
#include "../config/config.h"
#include <climits>
//temporary
#include <iostream>
//下 左  右  上
enum DIR{
    dir_down = 0,
    dir_left,
    dir_right,
    dir_up
};

struct BlockProp{
    bool solid_; 
    int harm_;
    BlockProp(bool solid = true, int harm = 0)
        :solid_(solid),harm_(harm) {}
    BlockProp(const BlockProp& block) 
    { 
        this->solid_ = block.solid_;
        this->harm_  = block.harm_;
    }
    //BlockProp& operator= (const Blcok&); 
};
#endif //ifndef STDINCS_H_
