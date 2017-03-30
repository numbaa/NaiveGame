#ifndef INPUT_H_
#define INPUT_H_
#include "../misc/stdincs.h"
#include "command.h"
using std::shared_ptr;

/* 
 * Input类是一个抽象类，它派生出诸如PlayerInput、MonsterInput类。
 * update()时，可能是要处理按键输入、可能是AI输入，总之，最终会
 * 形成一个Command队列，以供后续Physics更新使用。
 */
class Input {
public:
    virtual void update() = 0;
private:
    //维护一个Command队列数据结构，update()时插入队列，然后应该有一个get()之类的
    //函数，依次取出Command，取空为止
};

#endif //ifndef INPUT_H_
