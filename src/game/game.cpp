#include "game.h"

void Game::addScene(shared_ptr<Scene> scene)
{
    scenes_.push_back(scene);
    scenes_id_[ scene->getName() ] = scenes_.size() - 1;
}

void Game::switchScene(std::string name, uint32_t x, uint32_t y)
{
    scenes_[ active_scene_ ]->delEntity(player_);
    active_scene_ = scenes_id_[ name ];
    player_->setX(x);
    player_->setY(y);
    scenes_[ active_scene_ ]->addEntity(player_);
}

void Game::loop()
{
    scenes_[ active_scene_ ]->update(camera_);
}
