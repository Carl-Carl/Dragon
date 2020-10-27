/*
 * @Author: XHM
 * @Date: 2020-10-09 11:12:25
 * @LastEditTime: 2020-10-27 21:03:17
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
#define     VOICE_SEND_PIN      3 // 发射引脚
#define     FRONT_PIN           13
#define     LEFT_PIN            12
#define     RIGHT_PIN           2

/* Infrared pins */
#define     R_1                 A0
#define     R_2                 A1
#define     R_3                 A2
#define     R_4                 A3
#define     R_5                 A4
#define     R_6                 A5


/* Motor pins */
#define     SHOOT               4
#define     LEFT_E              5
#define     LEFT_1              8
#define     LEFT_2              7
#define     RIGHT_E             6
#define     RIGHT_1             10
#define     RIGHT_2             9

/* Bluetooth pins */
#define     BTX                 0
#define     BRX                 1

/* 模拟输出最大值 */
#define     ANALOG_MAX          90
#define     ANALOG_SLOW         70


/* 模式标志:
 * REMOTE_FLAG   : 遥控模式
 * INFRARED_FLAG : 红外模式
 * VOICE_FLAG    : 超声波模式
 */
enum MODE_FLAG {
    REMOTE_FLAG      =   9,
    INFRARED_FLAG    =   'a',
    VOICE_FLAG       =   'b',
};

/*
 * 0 : wait
 * 1 : forward
 * 2 : backward 
 * 3 : left
 * 4 : right
 * 5 : break
 * 6 : shoot
 */
enum orders {
    wait        =   0,
    forward     =   1,
    backward    =   2,
    left        =   3,
    right       =   4,
    brake       =   5,
    shoot       =   6,
    up          =   7,
    down        =   8,
};

extern orders Order;
extern int Modes;

#endif
