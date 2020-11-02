/*
 * @Author: Snowball
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-11-01 12:40:51
 * @LastEditors: Please set LastEditors
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
    u8 Mid;
    motor &control;

public:
    Infrared(motor &_control,u8 l3, u8 l2, u8 l1, u8 ri, u8 r2, u8 r3, u8 mid);
    void mode();
    int canStop();
};
#endif // !INFRARED
