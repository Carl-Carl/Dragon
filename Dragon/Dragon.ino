/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-11 21:04:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Dragon.ino
 */

#include "voice.h"
#include "motor.h"
#include "bluetooth.h"
#include "remote.h"

/* 
 * TEST 为1时，表示测试模式；TEST为0时，表示正式模式
 * 测试模式和正式模式的唯一区别在于loop()函数
 */
#define TEST 1

/*
 * 模式标志
 */
MODE_FLAG Modes;

/*
 * 遥控命令标志
 */
orders Order;

/******************** Initialization ********************/
motor motor_control(LEFT_E, RIGHT_E, LEFT_1, LEFT_2, RIGHT_1, RIGHT_2);
// bluetooth bluetooth_mode();
// remote remote_mode(motor_control);
voice voice_mode(motor_control, VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
/********************************************************/

/*
 *  初始化函数
 */
void setup ()
{
    Serial.begin(9600);
    Serial.println("setup OK");
    Modes = VOICE_FLAG;
}


#if TEST    // 测试模式
void loop()
{
    Serial.println("loop OK");
    voice_mode.mode();
}

#else   // 正式模式
void loop()
{
    switch (Modes) {
    case REMOTE_FLAG: // 遥控模式
        remote_mode.mode();
        break;

    case INFRARED_FLAG: // 红外模式
        ;
        break;

    case VOICE_FLAG: // 超声波模式
        voice_mode.mode();
        break;
    };
}

#endif
