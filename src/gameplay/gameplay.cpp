#include "gameplay.h"
#include <SDL/SDL.h>

shared_ptr<Entity> make_player()
{
    shared_ptr<Physics> phy(new PlayerPhysics);
    shared_ptr<Graphics> grph(new PlayerGraphics("./material/player/player1.png"));
    shared_ptr<Input> input(new PlayerInput);

    shared_ptr<Entity> player(new Person(phy, grph,input));
    return player;
}

shared_ptr<Scene> make_first_scene()
{
    shared_ptr<PhysicalSpace> space(new PhysicalSpace(1000, 1000));
    shared_ptr<Scene> scene(new Scene("./material/map/map_capture1.png", space, "first_scene"));
    return scene;
}

void Gameplay::run()
{
    Game::init();
    shared_ptr<Camera> camera(new Camera(640, 480));
    shared_ptr<Entity> player = make_player();
    Game mygame(player, camera);
    mygame.addScene(make_first_scene());
    mygame.switchScene("first_scene", 10, 10);

    mygame.loop();
}

Gameplay::Gameplay()
{
}

