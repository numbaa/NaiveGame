#ifndef GAME_H_
#define GAME_H_
#include "../misc/stdincs.h"
#include "../graphics/camera.h" //在类里有实例，不能只是class Camera;
#include <vector>
#include <map>
using std::shared_ptr;

/* Game 类是游戏循环的核心，它要做的是更新active_scene_索引的那个Scene
 * 注意，暴露给Game类的不是什么 Player 类，而是Entity类。
 * Player类应交由gameplay模块（不是Gameplay类）设计、使用，传过来只是一个指针，
 * 通过运行时多态执行函数。
 */
class Scene;
class Entity;

class Game {
    //看官别被 Pool 误导了，我实在想不到好名字
    using ScenePool = std::vector<std::shared_ptr<Scene>>;
public:
    Game(shared_ptr<Entity> player, shared_ptr<Camera> camera) : active_scene_(-1), player_(player), camera_(camera){}
    void addScene(shared_ptr<Scene> scene);
    void setPlayer(const shared_ptr<Entity> player)
    {
        player_ = player;
    }
    //switchScene(name, x, y) 中的x, y，指Player到新场景后的座标
    void switchScene(std::string scene_name, uint32_t x, uint32_t y);
    void loop();
    static void init();
private:
    static bool         had_initialed;
    int32_t             active_scene_;
    shared_ptr<Entity>  player_;
    shared_ptr<Camera>  camera_;
    ScenePool           scenes_;
    std::map<std::string, int32_t> scenes_id_;
};
#endif //ifndef GAME_H_
