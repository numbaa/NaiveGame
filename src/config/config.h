#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PATH_MAP_CHAPTER_1          ("./material/map/map_capture1.png") 
//#define PATH_MAP_CHAPTER_2        ("./material/map/map_capture2.png") 

#define PATH_PLAYER_NUM_1           ("./material/player/player1.png")
//#define PATH_PALYER_NUM_TWO       ("./material/player/player2.png")

#define CHAPTER_1                   (1)
#define CHAPTER_2                   (2)
//...
#define PLAYER_1                    (1)
#define PLAUER_2                    (2)
//...

#define getMapPath(num)             PATH_MAP_CHAPTER_##num
#define getPlayerPath(num)          PATH_PLAYER_NUM_##num


//玩家1图片局部精灵图配置     
//临时测试用
#define PLAYER1_IMAGE_WIDTH    (256) 
#define PLAYER1_IMAGE_HEIGHT   (512)
#define PLAYER1_DIR_NUMS               (4)
#define PLAYER1_MOVE_STATE_NUMS        (4)
#define PLAYER1_SPRIT_WIDTH_PER        ( PLAYER1_IMAGE_WIDTH / PLAYER1_MOVE_STATE_NUMS )
#define PLAYER1_SPRIT_HEIGHT_PER       ( PLAYER1_IMAGE_HEIGHT / PLAYER1_DIR_NUMS )



#endif
