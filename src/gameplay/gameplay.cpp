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
//仅测试
shared_ptr<Entity> make_skill(uint32_t x,uint32_t y)
{
    string skill_name = "fireball";
    PictureSize imageInfo = getPictureSizeByName(skill_name);  //获取图片信息
    uint32_t blocks_width = imageInfo.num_of_blocks_width_;
    uint32_t blocks_height = imageInfo.num_of_blocks_height_;

    shared_ptr<Model> model(new Model(blocks_width,blocks_height));
    shared_ptr<Physics> phy(new SkillPhysics(x, y,model));
    phy->setSpeed_x(2);
    phy->setSpeed_y(1);

    shared_ptr<Sprite> sprite(new SkillSprite(skill_name));
    shared_ptr<Graphics> grph(new SkillGraphics(skill_name,sprite));

    shared_ptr<Entity> skill ( new Skill(phy,grph));
    return skill;
}
shared_ptr<Scene> make_first_scene()
{
    shared_ptr<Scene> scene = Scene::getInstance();
    string map_name = "chapter1";   
    PictureSize mapinfo = getPictureSizeByName(map_name);
    shared_ptr<PhysicalSpace> space(new PhysicalSpace(mapinfo.width_,mapinfo.height_));

    scene->init(map_name,space);
    //主动产生技能,仅测试用
    /*shared_ptr<Entity> skill = make_skill(10,10); 
    Scene::getInstance()->addEntity(skill);
    skill = make_skill(100,100);
    Scene::getInstance()->addEntity(skill);*/
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

    mygame.loop();
}

Gameplay::Gameplay()
{
}

