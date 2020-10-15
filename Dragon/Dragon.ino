/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-14 21:32:40
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Dragon.ino
 */

#include "voice.h"
#include "motor.h"
#include "bluetooth.h"
#include "remote.h"
#include "Infrared.h"

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

/*
 * Initialization
 */
motor motor_control(LEFT_E, RIGHT_E, LEFT_1, LEFT_2, RIGHT_1, RIGHT_2);
remote remote_mode(motor_control, SHOOT);
voice voice_mode(motor_control, VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
Infrared infrared_mode(motor_control, R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8);
bluetooth *bluetooth_mode;
/********************************************************/

/*
 *  初始化函数
 */
void setup ()
{
#if TEST
    bluetooth_mode = new bluetooth(9600);

    Modes = REMOTE_FLAG;
#else
    Modes = REMOTE_FLAG;
#endif

}


#if TEST    // 测试模式
void loop()
{   Serial.println("loop");
    remote_mode.mode();
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

    motor_control.wait();

    // 指示灯提示
    for (u8 i = 0; i < 3; ++i) {
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(100);
    }
}

#endif
