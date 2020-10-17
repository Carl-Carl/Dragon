/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:14
 * @LastEditTime: 2020-10-12 15:46:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.h
 */
#ifndef REMOTE
#define REMOTE

#include "motor.h"
#include "Interface.h"
#include "Servo.h"

class remote
{
    motor &control;
    u8 shoot_pin;
    Servo shootgun;
    void fire();
    
public:
    remote(motor &_control, u8 shoot_pin);
    // 启动遥控模式
    void mode();
};






#endif // !REMOTE