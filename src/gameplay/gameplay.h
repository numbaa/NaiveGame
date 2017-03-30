#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_
#include "../misc/stdincs.h"
#include "../game/game.h"
#include "../input/input.h"
#include "../physics/physics.h"
#include "../graphics/graphics.h"
#include "../scene/scene.h"
#include "../entity/entity.h"
//以上这些头文件，将来可能作为 引擎 的公开头文件，放在一个地方，
//供gameplay使用。

// Gameplay 这个类，与游戏引擎部份分开，专门处理游戏性的内容
// 这个类可能比较杂乱，因为需要经常改动
class Gameplay {
public:
    Gameplay();
};

/* 
 * 如果我要创建一个玩家控制的角色，可以这样做：
 * shared_ptr<Entity> player(make_player(inp, phy, grp));
 * 这3个参数inp phy grp分别是
 *      shared_ptr<Input>、shared_ptr<Physics>、shared_ptr<Graphics>对象
 * 其中的Input、Physics、Graphics是抽象类
 * 也就是说，我可以这样使用Input类：
 *      player->input->derived_fun1();
 *      player->input->derived_fun2();
 */

#endif //ifndef GAMEPLAY_H_
