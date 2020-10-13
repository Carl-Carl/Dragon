/*
 * @Author: your name
 * @Date: 2020-10-10 15:28:59
 * @LastEditTime: 2020-10-12 10:15:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\voice.cpp
 */
#include "voice.h"
#include <stdlib.h>

voice::voice(motor &_control, u8 _send_pin, u8 _front_pin, u8 _left_pin, u8 _right_pin) : control(_control)
{
    this->send_pin = _send_pin;
    this->front_pin = _front_pin;
    this->left_pin = _left_pin;
    this->right_pin = _right_pin;

    pinMode(send_pin, OUTPUT);
    digitalWrite(send_pin, LOW);

    pinMode(front_pin, INPUT);
    pinMode(left_pin, INPUT);
    pinMode(right_pin, INPUT);

    Serial.println("voice OK");
}

void voice::get_dist(DIST_INFO &distance)
{    
    u16 *a[3] = {&distance.front, &distance.left, &distance.right};
    u8 ports[3] = {front_pin, left_pin, right_pin};
    u16 temp[8];

    for (u8 i = 0; i < 3; ++i) {
        // 取平均值
        for (u8 j = 0; j < 8; ++j) {
            // send begin order
            digitalWrite(send_pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(send_pin, LOW);

            temp[j] = pulseIn(ports[i], HIGH, 10000)/59;
        }

        // sort and get the average
        qsort(temp, 8, sizeof(u16), [](const void *a, const void *b) { return (int)(*(int*)a < *(int*)b); });
        
        *a[i] = 0;
        for (u8 j = 2; j < 6; ++j)
            *a[i] += temp[j];
        
        *a[i] >>= 2;
    }
}

void voice::mode()
{
    while (Modes == VOICE_FLAG) {
        // get distance information
        DIST_INFO distance;
        get_dist(distance);
        int lr = distance.left - distance.right;

        Serial.print("front: ");
        Serial.println(distance.front);
        Serial.print("left: ");
        Serial.println(distance.left);
        Serial.print("right: ");
        Serial.println(distance.right);
        Serial.println();

        // 紧急后退，避免撞击
        if (distance.front < 5) {
            control.backward();
            delay(400);
            continue;
        }

        // control the motor
        u8 speed = (distance.front > 40) ? ANALOG_MAX : ANALOG_SLOW;  // 判断：弯道 或 直道

        if (distance.left > 30 && distance.right > 30) {
            control.forward(speed);
            
        } else if (lr >= 3) {
            control.turn_left(speed);
            
        } else if (lr <= -3) {
            control.turn_right(speed);
            
        } else {
            control.forward(speed);
            
        }
<<<<<<< HEAD

        delay(200);
=======
>>>>>>> ae28b63b02e9127af43485a0b3944754eb4ade03
    }
}
