/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:14
 * @LastEditTime: 2020-10-11 09:22:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.h
 */
#ifndef REMOTE
#define REMOTE

#include "motor.h"
#include "Interface.h"

class remote
{
    motor &control;
public:
    remote(motor &_control);
    // 启动遥控模式
    void mode();
};




#endif // !REMOTE