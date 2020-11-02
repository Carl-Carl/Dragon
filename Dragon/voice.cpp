/*
 * @Author: your name
 * @Date: 2020-10-10 15:28:59
 * @LastEditTime: 2020-11-01 13:07:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\voice.cpp
 */
#include "voice.h"
#include "Infrared.h"
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
    u16 temp[10];

    for (u8 i = 1; i < 3; ++i) {
        // 取平均值
        for (u8 j = 0; j < 10; ++j) {
            // send begin order
            digitalWrite(send_pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(send_pin, LOW);

            temp[j] = pulseIn(ports[i], HIGH, 15000);

            delay(1);
        }

        // sort and get the average
        qsort(temp, 10, sizeof(u16), [](const void *a, const void *b) { return (int)(*(int*)a < *(int*)b); });
        
        *a[i] = 0;
        for (u8 j = 3; j < 7; ++j)
            *a[i] += temp[j];
        
        *a[i] >>= 2;
    }
}

int voice::get_dis_front()
{
    u16 tot[4];
    for (u8 i = 0; i < 4; ++i) {
        digitalWrite(send_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(send_pin, LOW);
        tot[i] = pulseIn(front_pin, HIGH, 150000);
    }

    return (tot[1] + tot[2]) >> 1;
}

const auto OFF_SET = 0;

void voice::mode()
{
    while (Modes == VOICE_FLAG) {
        // get distance information
        DIST_INFO distance;
        get_dist(distance);

        u16 front =  100;
        u16 left  = (distance.left  < 50) ? 100 : distance.left  / time_change;
        u16 right = (distance.right < 50) ? 100 : distance.right / time_change;

        double lr = (double)distance.left / distance.right;
        u8 speed = ANALOG_MAX + 20;
        // lr = lr > 1.5 ? 1.5 : lr;
        // lr = lr < 0.67 ? 0.67 : lr;

        Serial.println(front);
        Serial.println(left);
        Serial.println(right);
        Serial.println(lr);
        Serial.println();

        // 紧急后退，避免撞击
        int time;
        if (front <= 10) {
            control.backward();
            time = 200;
        } else if (lr >= 1.5) {   // 大转弯
            speed += 50;
            control.forward(speed >> 1, speed);
            // delay(150);
            // control.forward(speed, speed);
            time = 250;
        } else if (lr <= 0.667) {
            speed += 50;
            control.forward(speed, speed >> 1);
            // delay(150);
            // control.forward(speed, speed);
            time = 250;
        } else {
            control.forward(speed, speed);
            time = 300;
        }

        delay(time);
        control.brake();
        delay(300);
    }
}
