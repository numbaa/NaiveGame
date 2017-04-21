#include "gameplay.h"
#include <SDL/SDL.h>

void initKeyBoardMap();

shared_ptr<Entity> make_player()
{
    shared_ptr<Input> input(new PlayerInput);
    shared_ptr<Physics> phy(new PlayerPhysics);
    shared_ptr<Graphics> grph(new PlayerGraphics("player.png"));
    shared_ptr<Entity> entity(new Entity(input, phy, grph));
    return entity;
}

shared_ptr<Scene> make_first_scene()
{
    PhysicalSpace* space = new PhysicalSpace(1000, 1000);
    shared_ptr<Scene> scene(new Scene("map.png", space, "first_scene"));
    return scene;
}

void Gameplay::run()
{
    SDL_Init(SDL_INIT_EVERYTHING );
    initKeyBoardMap();
    Game mygame(nullptr);   
    mygame.setPlayer(make_player());
    mygame.addScene(make_first_scene());
    mygame.switchScene("first_scene", 10, 10);

    mygame.loop();
}

Gameplay::Gameplay()
{
}

