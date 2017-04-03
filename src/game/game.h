#ifndef GAME_H_
#define GAME_H_
#include "../misc/stdincs.h"
#include "../scene/scene.h"
#include "../entity/entity.h"
#include <vector>
#include <map>

/* Game 类是游戏循环的核心，它要做的是更新active_scene_索引的那个Scene
 * 注意，暴露给Game类的不是什么 Player 类，而是Entity类。
 * Player类应交由gameplay模块（不是Gameplay类）设计、使用，传过来只是一个指针，
 * 通过运行时多态执行函数。
 */
class Game {
    //看官别被 Pool 误导了，我实在想不到好名字
    using ScenePool = std::vector<std::shared_ptr<Scene>>;
public:
    Game() : active_scene_(-1) {}
    void addScene(shared_ptr<Scene> scene);
    //switchScene(name, x, y) 中的x, y，指Player到新场景后的座标
    void switchScene(std::string scene_name, uint32_t x, uint32_t y);
    void loop();
private:
    int32_t             active_scene_;
    Camera              camera_;
    ScenePool           scenes_;
    shared_ptr<Entity>  player_;
    std::map<std::string, int32_t> scenes_id_;
};

#endif //ifndef GAME_H_
