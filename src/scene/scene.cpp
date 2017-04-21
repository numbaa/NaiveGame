#include "scene.h"
#include "../entity/entity.h"
#include "../scene/background.h"
#include <algorithm>

Scene::Scene(std::string filename, PhysicalSpace* space, std::string scene_name)
    : bg_(std::make_shared<Background>(Background(filename))),
        space_(space),
        name_(scene_name)
{
}

void Scene::addEntity(shared_ptr<Entity> entity)
{
    entities_.push_back(entity);
    space_->addModel(entity);
}

void Scene::delEntity(shared_ptr<Entity> entity)
{
    entities_.erase(std::find(entities_.begin(), entities_.end(), entity));
    space_->delModel(entity);
}

void Scene::update(Camera& camera)
{
    for (auto& entity : entities_)
    {
        entity->update(*space_, camera);
    }
    bg_->blit(0, 0, camera.getWidth(), camera.getHeight(), camera);//这个也是临时的
    //camera.refresh();//传什么参？目的是让主角出现在屏幕中央，似乎应该传Player，那怎么找到Player？
                     //暂时这样吧，下次再改
}
