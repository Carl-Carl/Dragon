<<<<<<< HEAD
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
        Infrared(motor &_control, u8 l4, u8 l3, u8 l2, u8 l1, u8 ri, u8 r2, u8 r3, u8 r4);
        void get_Infrared(Infrared_Info &signal);
        void mode();

};
=======
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
        Infrared(motor &_control, u8 l4, u8 l3, u8 l2, u8 l1, u8 ri, u8 r2, u8 r3, u8 r4);
        void get_Infrared(Infrared_Info &signal);
        void mode();

};
>>>>>>> ae28b63b02e9127af43485a0b3944754eb4ade03
