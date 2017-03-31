#include "command.h"
#include <SDL/SDL_keysym.h>
#include <vector>
#include <iostream>

using std::shared_ptr;
using std::vector;
using std::make_shared;
Command:: Command()
     :type_(NOCOMMADN),value_(NOKEY)
{
    ;
}
void Command :: setCommand(ctype_t type,keyvalue_t value)
{
    type_ = type;
    value_ = value;
}
ctype_t Command:: getType(void)
{
    return type_;
}
keyvalue_t Command:: getValue(void)
{
    return value_;
}
// 仅供Player
// 323是所有按键的类型数量
// 每一项可以存放一个command
// 目的是为了隔离实际键盘事件和命令
vector <shared_ptr < Command> > KeyBoardMap_Up(323);      //按键释放  映射表
vector <shared_ptr < Command> > KeyBoardMap_Down(323);    //按键按下  映射表

//个性化设置按键:需要时编写
void setKeyBoardMap()
{
    ;
}
//映射表初始化：映射上下左右命令,默认以键盘的上下左右按键挂载
void initKeyBoardMap(void)      
{
    shared_ptr<Command> Elem(new Command);
    //挂载方向键 上:按下
    Elem->setCommand(MOVE_ON,DIR_UP);    //设置命令：移动，方向是'上‘,类型是按下按下键 
    KeyBoardMap_Down[SDLK_UP] = Elem;
    Elem.reset(new Command);
    //挂载防线键 上:放开
    Elem->setCommand(MOVE_OFF,DIR_UP);    
    KeyBoardMap_Up  [SDLK_UP] = Elem;
    Elem.reset(new Command);
    
    Elem->setCommand(MOVE_ON,DIR_DOWN);     
    KeyBoardMap_Down[SDLK_DOWN] = Elem;
    Elem.reset(new Command);

    Elem->setCommand(MOVE_OFF,DIR_DOWN); //设置命令： 移动，方向是'下’,类型是释放按键
    KeyBoardMap_Up  [SDLK_DOWN] = Elem;
    Elem.reset(new Command);
   
    Elem->setCommand(MOVE_ON,DIR_LEFT);     
    KeyBoardMap_Down[SDLK_LEFT] = Elem;
    Elem.reset(new Command);

    Elem->setCommand(MOVE_OFF,DIR_LEFT);     
    KeyBoardMap_Up  [SDLK_LEFT] = Elem;
    Elem.reset(new Command);
    
    Elem->setCommand(MOVE_ON,DIR_RIGHT);     
    KeyBoardMap_Down[SDLK_RIGHT] = Elem;
    Elem.reset(new Command);

    Elem->setCommand(MOVE_OFF,DIR_RIGHT);     
    KeyBoardMap_Up  [SDLK_RIGHT] = Elem;
    Elem.reset(new Command);
    
    /*std::cout<<"KeyBoardMap init down"<<std::endl;
    std::cout<<"test:"<<std::endl;
    auto it = KeyBoardMap_Down[SDLK_UP];
    std::cout<<"Command type :"<<it->getType()<<std::endl;
    std::cout<<"COmmand value:"<<it->getValue()<<std::endl;
    it = KeyBoardMap_Up[SDLK_UP];
    std::cout<<"Command type :"<<it->getType()<<std::endl;
    std::cout<<"COmmand value:"<<it->getValue()<<std::endl;*/
}

