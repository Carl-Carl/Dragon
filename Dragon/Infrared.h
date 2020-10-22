/*
 * @Author: Snowball
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-22 14:39:16
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Infrared.h
 */
#ifndef INFRARED
#define INFRARED

#include"Interface.h"
#include"motor.h"
/*
*Infrared_Info 用于存储红外模块传回的信号
*/
class Infrared
{
    u8 left3;
    u8 left2;
    u8 left1;
    u8 right1;
    u8 right2;
    u8 right3;
    motor &control;

public:
    Infrared(motor &_control,u8 l3, u8 l2, u8 l1, u8 ri, u8 r2, u8 r3);
    void mode();
    bool canStop();

};
#endif // !INFRARED
