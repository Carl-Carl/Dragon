/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-10 15:43:40
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
enum MODE_FLAG {
    remote_flag      =   0,
    infrared_flag    =   1,
    voice_flag       =   2,
} Modes;

/******************** 超声波 ********************/
/* 超声波模式 */
dist voice_mode(VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
/* 超声波距离信息 */
DIST_INFO v_dist_info;
/***********************************************/


/******************** 遥控 ********************/
/* 遥控模式 */
motor motor_control(LEFT_E, RIGHT_E, LEFT_1, LEFT_2, RIGHT_1, RIGHT_2);
/***********************************************/


/*
 *  初始化函数
 */
void setup ()
{
    Serial.begin(9600);
    Modes = remote_flag;
}


#if TEST    // 测试模式
void loop()
{
    voice_mode.get_dist(v_dist_info);
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
    switch (Modes) {
    case remote: // 遥控模式
        remote_mode.mode();
        break;
    
    case infrared: // 红外模式
        ;
        break;

    case voice: // 超声波模式
        ;
        break;
    };
}

#endif
