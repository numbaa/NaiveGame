#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
#include "game.h"
#include "input.h"
#include "physics.h"
#include "graphics.h"
#include "scene.h"
#include "entity.h"
//以上这些头文件，将来可能作为 引擎 的公开头文件，放在一个地方，
//供gameplay使用。

// Gameplay 这个类，与游戏引擎部份分开，专门处理游戏性的内容
// 这个类可能比较杂乱，因为需要经常改动
class Gameplay {
public:
    Gameplay();
};

#endif //ifndef GAMEPLAY_H_
