#ifndef SCENE_H_
#define SCENE_H_
#include "../misc/stdincs.h"
#include "../entity/entity.h"
#include "../graphics/camera.h"
#include "physicalspace.h"
#include "background.h"
#include <vector>
#include <string>
using std::shared_ptr;

class Scene {
    using EntityPool = std::vector<std::shared_ptr<Entity>>;
private:
    void finalUpdate(Camera& camera);
public:
    //map file是一个图片文件，初始化Scene时载入图片，
    //并将载入数据交由bg_管理，同时还要初始化相应大小的space_
    Scene(std::string map_filename, std::string scene_name);
    void update(Camera& camera);
    //每次addEntity，除了要在entities_中添加外，还要在space_中添加
    void addEntity(shared_ptr<Entity> entity);
    void delEntity(shared_ptr<Entity> entity);
    std::string getName() const;
private:
    shared_ptr<Background>  bg_;
    std::string             name_;
    EntityPool              entities_;
    //这个space_，顾名思义，存的是一个物理世界，它记录了整个Scene中
    //哪些区域不可到达，每个Entity具体占用场景哪些空间，等等
    PhysicalSpace          space_;
};

/* 对update函数的初步设想是这样的
 * void Scene::update(Camera& camera)
 * {
 *      for (auto entity : entities_)
 *      {
 *          entity->update(space_, camera);
 *      }
 *      updateBackground(Camera& camera);
 * }
 */

#endif //ifndef SCENE_H_
