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

//template<typename T>
//int getPathByName(string dest,string& path,T& a)
//缺陷:不要出现重名
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
