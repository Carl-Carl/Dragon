/*
 * @Author: XHM
 * @Date: 2020-10-10 12:26:35
 * @LastEditTime: 2020-10-10 16:07:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\motor.h
 */
#ifndef MOTOR
#define MOTOR

#include "Interface.h"


class motor
{
    u8 le;
    u8 l1;
    u8 l2;
    u8 re;
    u8 r1;
    u8 r2;
    
public:
    // 构造函数，初始化引脚
    motor(u8 le, u8 re, u8 l1, u8 l2, u8 r1, u8 r2);
    
    void forward();
    void backward();
    void turn_left();
    void turn_right();
    void brake();
};

#endif // !MOTOR
