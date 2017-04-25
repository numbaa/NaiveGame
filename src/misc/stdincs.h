#ifndef STDINCS_H_
#define STDINCS_H_
/*
 * 所谓 stdincs.h，即为 Standard Include Headers
 * 用来包括一些项目组几乎每个文件都会用到的标准头文件
 */

#include <memory>
#include <cstdint>
#include "../config/config.h"

enum DIR{
    dir_up = 0,
    dir_down,
    dir_left,
    dir_right
};
#endif //ifndef STDINCS_H_
