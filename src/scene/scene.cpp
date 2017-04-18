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
    finalUpdate(camera);
}
