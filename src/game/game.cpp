#include "game.h"
#include "../scene/scene.h"
#include "../entity/entity.h"
#include "../input/command.h"
#include <SDL/SDL_timer.h>  //临时控制帧率

bool Game::had_initialed = false;

void Game::addScene(shared_ptr<Scene> scene)
{
    scenes_.push_back(scene);
    scenes_id_[ scene->getName() ] = scenes_.size() - 1;
}

void Game::switchScene(std::string name, uint32_t x, uint32_t y)
{
    if (active_scene_ != -1)
    {
        scenes_[ active_scene_ ]->delPlayer();
    }
    active_scene_ = scenes_id_[ name ];
    player_->setX(x);
    player_->setY(y);
<<<<<<< HEAD
    scenes_[ active_scene_ ]->addEntity(player_);
    //...
=======
    scenes_[ active_scene_ ]->addPlayer(player_);
    camera_->changeBackground( scenes_[ active_scene_ ]->bg_ );
>>>>>>> efa33502d504ac764d96baa3f8d874570f998e52
}

void Game::loop()
{
    while (true)
    {
        scenes_[ active_scene_ ]->update(camera_);
    }
}

void Game::init()
{
    if (had_initialed == true)
        return;
    SDL_Init(SDL_INIT_EVERYTHING);
    initKeyBoardMap();
    had_initialed = true;
}
