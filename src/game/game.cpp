#include "game.h"
#include "../scene/scene.h"
#include "../entity/entity.h"
#include <SDL/SDL_timer.h>  //临时控制帧率

void Game::addScene(shared_ptr<Scene> scene)
{
    scenes_.push_back(scene);
    scenes_id_[ scene->getName() ] = scenes_.size() - 1;
}

void Game::switchScene(std::string name, uint32_t x, uint32_t y)
{
    if (active_scene_ != -1)
    {
        scenes_[ active_scene_ ]->delEntity(player_); //切换场景之前删除玩家？
    }
    active_scene_ = scenes_id_[ name ];
    player_->setX(x);
    player_->setY(y);
    scenes_[ active_scene_ ]->addEntity(player_);
    //...
}

void Game::loop()
{
    while (true)
    {
        SDL_Delay(200); //临时控制帧率
        scenes_[ active_scene_ ]->update(camera_);
    }
}
