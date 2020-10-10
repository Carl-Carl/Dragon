/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-10 14:42:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Dragon.ino
 */

#include "voice.h"
#include "motor.h"

/* 
 * TEST 为1时，表示测试模式；TEST为0时，表示正式模式
 * 测试模式和正式模式的唯一区别在于loop()函数
 */
#define TEST 1

/* 模式标志:
 * 0 : 遥控模式
 * 1 : 红外模式
 * 2 : 超声波模式
 */
u8 Modes = 0;

/* 超声波测距 */
dist distance(VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
/* 超声波距离信息 */
DIST_INFO v_dist_info;

void setup ()
{
    Serial.begin(9600);
}

#if TEST    // 测试模式
void loop()
{
    distance.get_dist(v_dist_info);
    Serial.print("front: ");
    Serial.println(v_dist_info.front);

    Serial.print("left: ");
    Serial.println(v_dist_info.left);

    Serial.print("right: ");
    Serial.println(v_dist_info.right);
    Serial.println("");
    delay(2000);
}

#else   // 正式模式
void loop()
{
    switch (Modes)
    {
    case 0: // 遥控模式
        ;
        break;
    
    case 1: // 红外模式
        ;
        break;

    case 2: // 超声波模式
        ;
        break;
    };
}

#endif
