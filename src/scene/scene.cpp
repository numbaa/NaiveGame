#include "scene.h"
#include "../entity/entity.h"
#include "../scene/background.h"
#include <algorithm>
#include <iostream>

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

//经过Physics类，传过来的entity 是个假的entity
//通过find，找出真正的那个
void Scene::kill(shared_ptr<Entity> entity)
{
    auto it = std::find(entities_.begin(),entities_.end(),entity);
    //already exists
    if(it == entities_.end())
    {
       exit(-1); 
    } 
    dead_entities_.push_back(*it);
}

void Scene::update(shared_ptr<Camera> camera)
{
    uint32_t curr = SDL_GetTicks();
    uint32_t lag = curr - last_update_;
    shared_ptr<Scene> curr_scene(this, [](Scene* p){ return; });
    auto entitiesTemp = entities_;
    while (lag  > UPDATE_GAP)
    {
        //Modify:将player统一到entities中，从此player和entity地位一样。
        //player_->updatePhysics(curr_scene, space_);
        //for (auto& entity : entities_)   
        //Modify:这里我碰到一个问题，SKILL产生的新entity一旦在for循环进行中添加进entities队列中，直接
        //导致了段错误,而本来是没有这个毛病的。这个现象应该是正常的，我不太确定。
        //我临时使用这个策略,暂时用一下
        for (auto& entity : entitiesTemp)
        {
            entity->updatePhysics(curr_scene, space_);
        }
        last_update_ = SDL_GetTicks();
        lag -= UPDATE_GAP;
    }
    if (curr-last_draw_ > DRAW_GAP)
    {
        //player_->updateImage(camera);
        //for (auto& entity : entities_)
        for (auto& entity : entitiesTemp)
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
        space_->delModel(*it);
        entities_.erase(it);
    }
    dead_entities_.clear();
}
