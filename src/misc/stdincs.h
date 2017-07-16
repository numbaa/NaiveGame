#ifndef STDINCS_H_
#define STDINCS_H_
/*
 * 所谓 stdincs.h，即为 Standard Include Headers
 * 用来包括一些项目组几乎每个文件都会用到的标准头文件
 */

#include <memory>
#include <cstdint>
#include "../config/config.h"

//temporary
#include <iostream>
//下 左  右  上
enum DIR{
    dir_down = 0,
    dir_left,
    dir_right,
    dir_up
};
#endif //ifndef STDINCS_H_
