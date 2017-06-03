#include "gameplay.h"
#include <SDL/SDL.h>
#include "../config/config.h"

//我日后在config中配置一下这些魔幻数字

shared_ptr<Entity> make_player()
{
    string player_name = "Gobulin";     //已在config.h中配置

    shared_ptr<Model> model(new Model(10, 21)); //每个Block宽6像素， 该模型宽10Block，高21Block
    shared_ptr<Physics> phy(new PlayerPhysics(150, 150, model));
    shared_ptr<Sprite> sprite(new PersonSprite(player_name, phy->getPos_x(), phy->getPos_y()));
    sprite->setColorKey(0xff, 0xff, 0xff);
    shared_ptr<Graphics> grph(new PlayerGraphics(player_name,sprite));   

    shared_ptr<Entity> player(new Person(phy, grph));
    return player;
}
//仅测试
shared_ptr<Entity> make_skill()
{
    string skill_name = "fireball";
    shared_ptr<Model> model(new Model(8,8));
    shared_ptr<Physics> phy(new SkillPhysics(100, 100,model));
    phy->setSpeed_x(0);

    shared_ptr<Sprite> sprite(new SkillSprite(skill_name));
    shared_ptr<Graphics> grph(new SkillGraphics(skill_name,sprite));

    shared_ptr<Entity> skill ( new Skill(phy,grph));
    return skill;
}
shared_ptr<Scene> make_first_scene()
{
    string map_name = "chapter1";   
    PictureSize mapinfo = getPictureSizeByName(map_name);
    shared_ptr<PhysicalSpace> space(new PhysicalSpace(mapinfo.width_,mapinfo.height_));
    shared_ptr<Scene> scene(new Scene(map_name, space, "first_scene")); //建议以地图名字命名场景
    //主动产生技能,仅测试用
    shared_ptr<Entity> skill = make_skill(); 
    scene->addEntity(skill);
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

