/*
 * @Author: Snowball
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-19 08:03:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Infrared.h
 */
#include"Interface.h"
#include<stdlib.h>
#include"motor.h"

/*
*Infrared_Info 用于存储红外模块传回的信号
*/

struct Infrared_Info
{
    u8 left[4];
    u8 right[4];
};


class Infrared
{
    u8 left4;
    u8 left3;
    u8 left2;
    u8 left1;
    u8 right1;
    u8 right2;
    u8 right3;
    u8 right4;
    motor &control;

public:
    bool canStop();
    Infrared(motor &_control, u8 l4, u8 l3, u8 l2, u8 l1, u8 ri, u8 r2, u8 r3, u8 r4);
    void get_Infrared(Infrared_Info &signal);
    void mode();

};
