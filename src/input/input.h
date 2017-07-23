#ifndef INPUT_H_
#define INPUT_H_
#include "../misc/stdincs.h"
#include "command.h"
#include <queue>

using std::queue;
using std::shared_ptr;
using std::make_shared;

/* 
 * Input类是一个抽象类，它派生出诸如PlayerInput、MonsterInput类。
 * update()时，可能是要处理按键输入、可能是AI输入，总之，最终会
 * 形成一个Command队列，以供后续Physics更新使用。
 */
class Input {
public:
    virtual void update() = 0;
    virtual ~Input() = default;
    virtual shared_ptr<Command> getCommand() = 0;
protected:
    queue <shared_ptr<Command>> cmdque_;
private:
    //维护一个Command队列数据结构，update()时插入队列，然后应该有一个get()之类的
    //函数，依次取出Command，取空为止
};

class PlayerInput: public Input{
public:
    virtual void update() override;
    virtual shared_ptr<Command> getCommand() override;
}; 

class NpcInput: public Input{
public:
    NpcInput();  
    void commandAdd(shared_ptr<Command>& cmd);//给NPC添加命令,AI可能需要这个接口
    virtual void update() override;
    virtual shared_ptr<Command> getCommand() override;
private:
    queue <shared_ptr <Command>> cmdinput_;  //虚构的命令输入
    queue <shared_ptr <Command>> cmdque_;
}; 
#endif //ifndef INPUT_H_
