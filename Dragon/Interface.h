/*
 * @Author: XHM
 * @Date: 2020-10-09 11:12:25
 * @LastEditTime: 2020-10-11 21:00:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Voiced:\Files\Arduino\Dragon\dragon.h
 */

/*
 * 文档说明：
 * "interface.h"文件包含了所有公共的宏定义、枚举类型和声明
 * 所有.h文件和主程序均需 #include "interface.h"
 * PS: 请勿在此直接定义变量
 */

#ifndef INTERFACE
#define INTERFACE
#include <arduino.h>

/* Voice pins */
#define     VOICE_SEND_PIN      2 // 发射引脚
#define     FRONT_PIN           3
#define     LEFT_PIN            4
#define     RIGHT_PIN           5

/* Infrared pins */
#define     R_1                 0
#define     R_2                 1
#define     R_3                 2
#define     R_4                 3
#define     R_5                 4
#define     R_6                 5
#define     R_7                 6
#define     R_8                 7

/* Motor pins */
#define     LEFT_E              10
#define     LEFT_1              8
#define     LEFT_2              9
#define     RIGHT_E             11
#define     RIGHT_1             12
#define     RIGHT_2             13

/* Bluetooth pins */
#define     BTX                 0
#define     BRX                 1

/* 模拟输出最大值 */
#define     ANALOG_MAX          20
#define     ANALOG_SLOW         5


/* 模式标志:
 * REMOTE_FLAG   : 遥控模式
 * INFRARED_FLAG : 红外模式
 * VOICE_FLAG    : 超声波模式
 */
enum MODE_FLAG {
    REMOTE_FLAG      =   0,
    INFRARED_FLAG    =   1,
    VOICE_FLAG       =   2,
};

/*
 * 0 : wait
 * 1 : forward
 * 2 : backward 
 * 3 : left
 * 4 : right
 * 5 : break;
 */
enum orders {
    wait        =   0,
    forward     =   1,
    backward    =   2,
    left        =   3,
    right       =   4,
    brake       =   5,
};

extern orders Order;
extern MODE_FLAG Modes;

#endif // !DRAGON
