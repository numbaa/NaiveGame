#ifndef COMMAND_H_
#define COMMAND_H_
#include "stdincs.h"

//命令类型
typedef enum CommandType{
    NOCOMMADN = 0,
    MOVE_ON,
    MOVE_OFF,
    SKILL_ON,
    SKILL_OFF
}ctype_t;
//命令值
typedef enum KeyValue{
    NOKEY = 0,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    SKILL1,    
    SKILL2,
    SKILL3
}keyvalue_t;
class  Command{
public:
    Command();
    void setCommand(ctype_t,keyvalue_t);       
    ctype_t getType();
    keyvalue_t getValue();
private:
    ctype_t type_;
    keyvalue_t value_; 
};
#endif //ifndef COMMAND_H_
