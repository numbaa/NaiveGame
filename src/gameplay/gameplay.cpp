#include "gameplay.h"

shared_ptr<Entity> make_player()
{
    shared_ptr<Input> input(new PlayerInput);
    shared_ptr<Physics> phy(new PlayerPhysics);
    shared_ptr<Graphics> grph(new PlayerGraphics);
    shared_ptr<Entity> entity(new Entity(input, phy, grph));
    return entity;
}

shared_ptr<Scene> make_first_scene()
{
    PhysicalSpace* space = new PhysicalSpace(1000, 1000);
    //TODO:change
    shared_ptr<Scene> scene(new Scene("mapfile.png", space, "first_scene"));
    return scene;
}

void Gameplay::run()
{
    Game mygame(make_player());
    mygame.addScene(make_first_scene());
    mygame.switchScene("first_scene", 100, 100);

    mygame.loop();
}

