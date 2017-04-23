#ifndef SCENE_H_
#define SCENE_H_
#include "../misc/stdincs.h"
//#include "../entity/entity.h"
#include "../graphics/camera.h"
#include "physicalspace.h"
//#include "background.h"
#include <vector>
#include <string>
using std::shared_ptr;

class Entity;
class Background;

class Scene {
    friend class Game;
    using EntityPool = std::vector<std::shared_ptr<Entity>>;
public:
    //map file是一个图片文件，初始化Scene时载入图片，
    //并将载入数据交由bg_管理
    Scene(std::string map_filename, shared_ptr<PhysicalSpace> space, std::string scene_name);
    void update(shared_ptr<Camera> camera);
    //每次addEntity，除了要在entities_中添加外，还要在space_中添加
    void addEntity(shared_ptr<Entity> entity);
    void delEntity(shared_ptr<Entity> entity);
    void addPlayer(shared_ptr<Entity> player);
    void delPlayer();
    std::string getName() const { return name_; }
protected:
    shared_ptr<Background>  bg_;
private:
    std::string             name_;
    shared_ptr<PhysicalSpace> space_;
    EntityPool              entities_;
    shared_ptr<Entity>      player_;
    uint32_t                last_update_;
    uint32_t                last_draw_;
    //这个space_，顾名思义，存的是一个物理世界，它记录了整个Scene中
    //哪些区域不可到达，每个Entity具体占用场景哪些空间，等等
};

/* 对update函数的初步设想是这样的
 * void Scene::update(Camera& camera)
 * {
 *      for (auto entity : entities_)
 *      {
 *          entity->update(space_, camera);
 *      }
 *      finalUpdate(camera);
 * }
 */

#endif //ifndef SCENE_H_
