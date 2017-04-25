#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <map>
#include <string>

using std::string;
using std::map;

//路径配置
#define PATH_MAP_CHAPTER_1          ("./material/map/map_capture1.png") //路径
#define MAP_CHAPTER_1_NAME          ("chapter1")   //地图别名


#define PATH_PLAYER_NUM_1           ("./material/player/player1.png")   //路径
#define PLAYER_NUM_1_NAME           ("Gobulin")    //别名,哥布林


#define PATH_SKILL_1                ("./material/skill/skill1/fireball.png") //路径
#define SKILL_1_NAME                ("fireball")  //别名,火球
//...

#define getMapPath(num)             PATH_MAP_CHAPTER_##num
#define getPlayerPath(num)          PATH_PLAYER_NUM_##num


//图片配置
//为了统一，效果简单的技能采用未分割的图片(所有技能效果在一张图上的)
//效果炫酷的可以采用分割的图片

#define SKILL_1_TYPE                ("complete") //完整
#define SKILL_1_WIDTH               (480)
#define SKILL_1_HEIGHT              (80)        
#define SKILL_1_PART                (6)          //由6小块组成

string getPathByName(string& name);
#endif
