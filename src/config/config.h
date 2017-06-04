#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <map>
#include <string>

#define BLOCK_SIZE     (6)

using std::string;
using std::map;
class PictureSize {
public:
    PictureSize(uint32_t width,uint32_t height,uint32_t row,uint32_t col,uint32_t blocks_width,uint32_t blocks_height) :width_(width),height_(height),row_(row),col_(col),num_of_blocks_width_(blocks_width),num_of_blocks_height_(blocks_height) {}

    uint32_t width_;    //实际宽度(像素)
    uint32_t height_;   //实际高度
    uint32_t row_;      //图片行数
    uint32_t col_;      //列数
    uint32_t num_of_blocks_width_;  //一个sprite占用的block数目
    uint32_t num_of_blocks_height_;
};
inline uint32_t promote(uint32_t val,uint32_t size)
{
    return (val%size ==0) ? (val/size) : (val/size + 1);
}
//路径配置
#define PATH_MAP_CHAPTER_1          ("./material/map/map_capture1.png") //路径
#define MAP_CHAPTER_1_NAME          ("chapter1")   //地图别名

#define PATH_PLAYER_NUM_1           ("./material/player/player1.png")   //路径
#define PLAYER_NUM_1_NAME           ("Gobulin")    //别名,哥布林

#define PATH_SKILL_1                ("./material/skill/skill1/fireball.png") //路径
#define SKILL_1_NAME                ("fireball")  //别名,火球
//...

#define getMapPathByMacro(num)             PATH_MAP_CHAPTER_##num
#define getPlayerPathByMacro(num)          PATH_PLAYER_NUM_##num


//图片尺寸信息配置
#define MAP_CHAPTER_1_WIDTH         (1940)
#define MAP_CHAPTER_1_HEIGHT        (1440)
#define MAP_CHAPTER_1_IMAGE_ROW     (1)
#define MAP_CHAPTER_1_IMAGE_COL     (1)
#define MAP_CHAPTER_1_BLOCKS_WIDTH  (promote(1940,BLOCK_SIZE)) 
#define MAP_CHAPTER_1_BLOCKS_HEIGHT (promote(1940,BLOCK_SIZE))

#define PLAYER_NUM_1_WIDTH          (256)
#define PLAYER_NUM_1_HEIGHT         (512)
#define PLAYER_NUM_1_IMAGE_ROW      (4)
#define PLAYER_NUM_1_IMAGE_COL      (4)
#define PLAYER_NUM_1_BLOCKS_WIDTH   (promote(65,BLOCK_SIZE))  //贴紧外围
#define PLAYER_NUM_1_BLOCKS_HEIGHT  (promote(95,BLOCK_SIZE)) 

//为了统一，效果简单的技能采用未分割的图片(所有技能效果在一张图上的)
//效果炫酷的可以采用分割的图片

#define SKILL_1_TYPE                ("complete") //完整
#define SKILL_1_WIDTH               (480)
#define SKILL_1_HEIGHT              (80)        
#define SKILL_1_IMAGE_ROW           (1)          //由6小块组成
#define SKILL_1_IMAGE_COL           (6)
#define SKILL_1_BLOCKS_WIDTH        (promote(55,BLOCK_SIZE)) 
#define SKILL_1_BLOCKS_HEIGHT       (promote(55,BLOCK_SIZE)) 

PictureSize getPictureSizeByName(string& name);
string getPathByName(string& name);

#endif  //_CONFIG_H_
