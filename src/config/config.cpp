#include "config.h"

const map<string,string> MapPathList = {
    {MAP_CHAPTER_1_NAME,PATH_MAP_CHAPTER_1},
    //...
};

const map<string,string> PlayerPathList = {
    {PLAYER_NUM_1_NAME,PATH_PLAYER_NUM_1},
    //...
};

const map<string,string> SkillPathList = {
    {SKILL_1_NAME,PATH_SKILL_1},
};

const map<string,PictureSize> PictureSizeList = {
    //PLAYER
    { PLAYER_NUM_1_NAME,PictureSize(
                        PLAYER_NUM_1_WIDTH,
                        PLAYER_NUM_1_HEIGHT,
                        PLAYER_NUM_1_IMAGE_ROW,
                        PLAYER_NUM_1_IMAGE_COL,
                        PLAYER_NUM_1_BLOCKS_WIDTH,
                        PLAYER_NUM_1_BLOCKS_HEIGHT)},
    //Skill
    { SKILL_1_NAME,     PictureSize(
                        SKILL_1_WIDTH,SKILL_1_HEIGHT,
                        SKILL_1_IMAGE_ROW,
                        SKILL_1_IMAGE_COL,
                        SKILL_1_BLOCKS_WIDTH,
                        SKILL_1_BLOCKS_HEIGHT) },
    //map
    { MAP_CHAPTER_1_NAME,PictureSize(
                        MAP_CHAPTER_1_WIDTH,
                        MAP_CHAPTER_1_HEIGHT,
                        MAP_CHAPTER_1_IMAGE_ROW,
                        MAP_CHAPTER_1_IMAGE_COL,
                        MAP_CHAPTER_1_BLOCKS_WIDTH,
                        MAP_CHAPTER_1_BLOCKS_HEIGHT)}
};
PictureSize getPictureSizeByName(string& name)
{
    PictureSize picturesize(0,0,0,0,0,0);
    auto it = PictureSizeList.find(name);
    if(it != PictureSizeList.end())
    {
        picturesize = it->second;
        return picturesize;
    }
    return picturesize;
}
//template<typename T>
//int getPathByName(string dest,string& path,T& a)
//缺陷:所有的图片名字不能出现重名,这是当前设计的问题
//因为Surface根据name获取路径的时候，不知道是Map还是Plaeyr...
//如果找不到,返回空字符串
string getPathByName(string& name)
{
    string path;
    auto it = MapPathList.find(name);
    if(it != MapPathList.end())
    {
        path = it->second;
        return path;
    } 
    it = PlayerPathList.find(name);
    if(it != PlayerPathList.end())
    {
        path = it->second;
        return path;
    }
    it = SkillPathList.find(name);
    if( it != SkillPathList.end())
    {
        path = it->second;
        return path;
    }
    return path;
}
