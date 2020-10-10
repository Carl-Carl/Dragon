/*
 * @Author: your name
 * @Date: 2020-10-09 10:32:24
 * @LastEditTime: 2020-10-10 15:32:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Voice\voice\voice.ino
 */
#ifndef VOICE
#define VOICE

#include <stdlib.h>
#include "Interface.h"

/*
 * DIST_INFO 对象用于存储超声波回传的信息
 * 成员 front, left 和 right 分别保存距离三个方向墙壁的距离，单位：cm。
*/
struct DIST_INFO {
    u16 front;
    u16 left;
    u16 right;
};

/*
 * dist 对象用于初始化超声波测距系统和进行超声波测距
 * dist() ：构造函数，会完成引脚的初始化工作
 * get_dist() ：会测量好距离，并打包成 DIST_INFO 对象
*/
class dist
{
    u8 send_pin;
    u8 front_pin;
    u8 left_pin;
    u8 right_pin;
  
public:
    dist(u8 _send_pin, u8 _front_pin, u8 _left_pin, u8 _right_pin);

    /* return the distance with cm */
    void get_dist(DIST_INFO &distance);
};

#endif
