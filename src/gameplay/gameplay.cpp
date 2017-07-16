#include "gameplay.h"
#include <SDL/SDL.h>
//#include "../config/config.h"


shared_ptr<Entity> make_player()
{
    string player_name = "Gobulin";     //已在config.h中配置
    PictureSize imageInfo = getPictureSizeByName(player_name);  //获取图片信息
    uint32_t blocks_width = imageInfo.num_of_blocks_width_;
    uint32_t blocks_height = imageInfo.num_of_blocks_height_;

    shared_ptr<Model> model(new Model(blocks_width,blocks_height)); 
    shared_ptr<Physics> phy(new PlayerPhysics(0, 0, model));
    shared_ptr<Sprite> sprite(new PersonSprite(player_name, phy->getPos_x(), phy->getPos_y()));
    sprite->setColorKey(0xff, 0xff, 0xff);
    shared_ptr<Graphics> grph(new PlayerGraphics(player_name,sprite));   
    shared_ptr<Entity> player(new Person(phy, grph));
    return player;
}

shared_ptr<Scene> make_first_scene()
{
    shared_ptr<Scene> scene = Scene::getInstance();
    string map_name = "chapter1";   
    PictureSize mapinfo = getPictureSizeByName(map_name);
    shared_ptr<PhysicalSpace> space(new PhysicalSpace(mapinfo.width_,mapinfo.height_));

    scene->init(map_name,space);
    return scene;
}

void Gameplay::run()
{
    Game::init();
    shared_ptr<Camera> camera(new Camera(640, 480));
    shared_ptr<Entity> player = make_player();

    Game mygame(player, camera);
    mygame.addScene(make_first_scene());
    mygame.switchScene("first_scene", 200, 200);
    //Scene::getInstance()->addEntity(player);     
    mygame.loop();
}

Gameplay::Gameplay()
{
}

