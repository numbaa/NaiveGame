#include "scene.h"
#include "../entity/entity.h"
#include "../scene/background.h"
#include <algorithm>
#include <iostream>

/*Scene::Scene(string name,shared_ptr<PhysicalSpace> space, std::string scene_name)
     :  bg_(std::make_shared<Background>(Background(name))),
        name_(scene_name),
        space_(space),
        player_(nullptr),
        last_update_(SDL_GetTicks()),
        last_draw_(SDL_GetTicks())
{
}*/
shared_ptr<Scene> Scene::instance_ = nullptr;
Scene::Scene()
    :bg_( nullptr ),
    space_(nullptr),
    player_(nullptr),
    last_update_(SDL_GetTicks()),
    last_draw_(SDL_GetTicks())
{
}
void Scene::init(string name,shared_ptr<PhysicalSpace>& space)
{
    bg_ = make_shared<Background> (Background(name));
    space_ = space;
    name_ = name;
}
void Scene::addEntity(shared_ptr<Entity> entity)
{
    auto it = std::find(entities_.begin(),entities_.end(),entity);
    //already exists
    if(it != entities_.end())
    {
        return;
    }
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

void Scene::kill(shared_ptr<Entity> entity)
{
    //std::cout<<"Scene killing entity: "<<entity.get()<<std::endl;
    dead_entities_.push_back(entity);
}

void Scene::update(shared_ptr<Camera> camera)
{
    uint32_t curr = SDL_GetTicks();
    uint32_t lag = curr - last_update_;
    shared_ptr<Scene> curr_scene(this, [](Scene* p){ return; });

    while (lag  > UPDATE_GAP)
    {
        player_->updatePhysics(curr_scene, space_);
        for (auto& entity : entities_)
        {
            entity->updatePhysics(curr_scene, space_);
        }
        last_update_ = SDL_GetTicks();
        lag -= UPDATE_GAP;
    }

    if (curr-last_draw_ > DRAW_GAP)
    {
        player_->updateImage(camera);
        for (auto& entity : entities_)
        {
            entity->updateImage(camera);
        }
        camera->refresh(player_->getX(), player_->getY());
        last_draw_ = SDL_GetTicks();
    }

    //entities_ 不适合使用std::vector，性能跟不上，日后改
    for (auto& et : dead_entities_)
    {
        auto it = std::find(entities_.begin(), entities_.end(), et);
        /*
        for (auto& ent : entities_)
        {
            std::cout<<"entity in entities_: "<<ent.get()<<std::endl;
        }
        if (it == entities_.end())
        {
            std::cout<<"Couldn't find entity: "<<et.get()<<std::endl;
            exit(-1);
        }
        */
        space_->delModel(*it);
        entities_.erase(it);
    }
    dead_entities_.clear();
}
