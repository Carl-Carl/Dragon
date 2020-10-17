/*
 * @Author: your name
 * @Date: 2020-10-10 15:28:59
 * @LastEditTime: 2020-10-17 09:03:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\voice.cpp
 */
#include "voice.h"
#include <stdlib.h>

/* Convert Microseconds to cm */
const int time_change = 59;

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
    u16 temp[6];

    for (u8 i = 0; i < 3; ++i) {
        // 取平均值
        for (u8 j = 0; j < 6; ++j) {
            // send begin order
            digitalWrite(send_pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(send_pin, LOW);

            temp[j] = pulseIn(ports[i], HIGH, 10000);
        }

        // sort and get the average
        qsort(temp, 6, sizeof(u16), [](const void *a, const void *b) { return (int)(*(int*)a < *(int*)b); });
        
        *a[i] = 0;
        for (u8 j = 1; j < 5; ++j)
            *a[i] += temp[j];
        
        *a[i] >>= 2;
    }
}

int voice::get_dis_front()
{
    digitalWrite(send_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(send_pin, LOW);

    return pulseIn(front_pin, HIGH, 10000);
}


void voice::mode()
{
    while (Modes == VOICE_FLAG) {
        // get distance information
        DIST_INFO distance;
        get_dist(distance);

        double lr = (double)distance.left / distance.right;
        u16 front = distance.front / time_change;
        u16 left = distance.left / time_change;
        u16 right = distance.right / time_change;

        u8 speed =  ANALOG_MAX;
        lr = lr > 1.5 ? 1.5 : lr;
        lr = lr < 0.67 ? 0.67 : lr;

        // 紧急后退，避免撞击
        if (front <= 5) {
            control.brake();
            delay(100);
            control.backward();
            delay(400);
            continue;
        } else if (front <= 15) {   // 大转弯
            control.brake();
            delay(200);

            if (lr > 1)
                control.turn_left(speed);
            else
                control.turn_right(speed);

            while (get_dis_front()/time_change <= 25);  // 等待前方空间足够大

        } else {    
            if (left > 40 || right > 40) {      // 弯道直行
                control.forward(speed, speed);
            } else if (lr >= 1.1) {
                control.forward(speed/lr, speed);
            } else if (lr <= 0.9) {
                control.forward(speed, speed*lr);
            } else {
                control.forward(speed, speed);
            }
        }
    }
}
