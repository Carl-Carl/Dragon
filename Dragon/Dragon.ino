/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-19 21:19:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Dragon.ino
 */

#include "voice.h"
#include "motor.h"
#include "TimerOne.h"
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
 * 启动标志
 */
bool start;

void signal();

/*
 * Initialization
 */
Servo shootgun;
motor motor_control(LEFT_E, RIGHT_E, LEFT_1, LEFT_2, RIGHT_1, RIGHT_2);
remote remote_mode(motor_control, shootgun, signal);
voice voice_mode(motor_control, VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
Infrared infrared_mode(motor_control, R_1, R_2, R_3, R_4, R_5, R_6);
/********************************************************/



/*
 *  初始化函数
 */
void setup ()
{
    Serial.begin(9600);
    shootgun.attach(11);
    Timer1.attachInterrupt(signal, 50000);  // 50ms 检查一次命令
    
#if TEST
    
    Modes = INFRARED_FLAG;
#else

    Modes = REMOTE_FLAG;
#endif

}


#if TEST    // 测试模式
void loop()
{   
    Serial.println("loop");
    infrared_mode.mode();
}

#else   // 正式模式
void loop()
{
    switch (Modes) {
    case REMOTE_FLAG: // 遥控模式
        remote_mode.mode();
        break;

    case INFRARED_FLAG: // 红外模式
        start = true;
        infrared_mode.mode();
        break;

    case VOICE_FLAG: // 超声波模式
        start = true;
        voice_mode.mode();
        break;
    };

    motor_control.wait();
}

#endif

/*
 * 蓝牙信号接收-中断服务函数
 */
void signal()
{
    char ch = Serial.read();

    if (ch != EOF) {
        if ('0' <= ch <= '6' && Modes == REMOTE_FLAG)
            Order = (orders)(ch - '0');
        else if ('7' <= ch && ch <= '9')
            Modes = (MODE_FLAG)(ch - '7');

        while (Serial.read() != EOF);
    }


    // if (Modes != REMOTE_FLAG && infrared_mode.canStop()) {
    //     motor_control.forward(ANALOG_MAX, ANALOG_MAX);

    //     if (start) {    // 启动时
    //         while (infrared_mode.canStop());
    //         start = false;
    //     } else {        // 停止时
    //         delay(800);
    //         Modes = REMOTE_FLAG;
    //     }

    //     motor_control.brake();
    // }
}
