#include "scene.h"
#include "../entity/entity.h"
#include "../scene/background.h"
#include <algorithm>
#include <iostream>

Scene::Scene(std::string filename, shared_ptr<PhysicalSpace> space, std::string scene_name)
     :  bg_(std::make_shared<Background>(Background(filename))),
        name_(scene_name),
        space_(space),
        player_(nullptr),
        last_update_(SDL_GetTicks()),
        last_draw_(SDL_GetTicks())
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

void Scene::addPlayer(shared_ptr<Entity> player)
{
    player_ = player;
}

void Scene::delPlayer()
{
    player_.reset();
}

void Scene::update(shared_ptr<Camera> camera)
{
    uint32_t curr = SDL_GetTicks();
    uint32_t lag = curr - last_update_;
    std::cout<<"curr: "<<curr<<"\tlast_update: "<<last_update_<<std::endl;
    while (lag  > UPDATE_GAP)
    {
        player_->update(space_);
        for (auto& entity : entities_)
        {
            entity->update(space_);
        }
        last_update_ = SDL_GetTicks();
        lag -= UPDATE_GAP;
    }

    if (curr-last_draw_ > DRAW_GAP)
    {
        player_->update(camera);
        for (auto& entity : entities_)
        {
            entity->update(camera);
        }
        camera->refresh(player_->getX(), player_->getY());
        last_draw_ = SDL_GetTicks();
    }
}
