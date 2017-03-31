#include "input.h"
#include <SDL/SDL.h>
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;

extern vector<shared_ptr<Command>> KeyBoardMap_Up;
extern vector<shared_ptr<Command>> KeyBoardMap_Down;

//用作按键判断，比如我仅设置了10个键，那么之外的键就是非法的
//或者干脆把不要的按键全部都MASK掉，不要让按键事件发生，提高
//效率
bool isLegal(SDLKey value)
{
    return value;
}

void PlayerInput::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN)
        {
            if(isLegal(event.key.keysym.sym))
            {
                shared_ptr <Command> cmd = KeyBoardMap_Down[event.key.keysym.sym];
                if(cmd == nullptr)
                    cerr<<"error:PlayerInput::update()"<<endl;
                cmdque_.push(cmd);
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(isLegal(event.key.keysym.sym))
            {
                shared_ptr <Command> cmd = KeyBoardMap_Up[event.key.keysym.sym];
                if(cmd == nullptr)
                    cerr<<"error:PlayerInput::update()"<<endl;
                cmdque_.push(cmd);
            }
        }
        else if(event.type == SDL_QUIT)
        {
            // sysFree();
        }
    }
}
//返回值!=nullptr代表还有命令未取出
//example:
//auto it = getCommand();
//while(it != nullptr)
//{
//  dosomething(it);
//  it = getCommand();
//}
shared_ptr<Command> PlayerInput :: getCommand(void)
{
    if(cmdque_.empty())
        return shared_ptr <Command>();     //null
    auto cmd = cmdque_.front();
    cmdque_.pop();
    return cmd;
}
