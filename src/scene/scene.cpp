#include "scene.h"
#include <algorithm>

std::string Scene::getName() const
{
    return name_;
}

Scene::Scene(std::string filename, PhysicalSpace* space, std::string scene_name)
    : bg_(std::make_shared<Background>(Background(filename))),
        space_(space),
        name_(scene_name)
{
}

void Scene::addEntity(shared_ptr<Entity> entity)
{
    entities_.push_back(entity);
    space_.addModel(entity);
}

void Scene::delEntity(shared_ptr<Entity> entity)
{
    entities_.erase(std::find(entities_.begin(), entities_.end(), entity));
    space_.delModel(entity);
}

void Scene::update(Camera& camera)
{
    for (auto& entity : entities_)
    {
        entity->update(space_, camera);
    }
    camera.refresh();//传什么参？目的是让主角出现在屏幕中央，似乎应该传Player，那怎么找到Player？
                     //暂时这样吧，下次再改
}
