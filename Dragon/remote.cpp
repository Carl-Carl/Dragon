/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:26
 * @LastEditTime: 2020-10-12 19:18:39
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.cpp
 */
#include "remote.h"

remote::remote(motor &_control, u8 _shoot_pin) : control(_control), shoot_pin(_shoot_pin)
{
    Order = wait;
    pinMode(shoot_pin, OUTPUT);
    digitalWrite(shoot_pin, LOW);
}

void remote::fire()
{
    digitalWrite(shoot_pin, HIGH);
    delay(100);
    digitalWrite(shoot_pin, LOW);
}

void remote::mode()
{
    Order = wait;
    digitalWrite(shoot_pin, LOW);
    
    while (Modes == REMOTE_FLAG) {
        switch (Order) {
        case forward:
            Serial.println("forward");
            control.forward(ANALOG_MAX, ANALOG_MAX);
            break;

        case backward:
//            Serial.println("backward");
            control.backward();
            break;

        case left:
//            Serial.println("left");
            control.turn_left(ANALOG_MAX);
            break;

        case right:
//            Serial.println("right");
            control.turn_right(ANALOG_MAX);
            break;

        case brake:
//            Serial.println("brake");
            control.brake();
            break;

        case shoot:
//            Serial.println("shoot");
            fire();
            break;
        }
        
        delay(50);
    }
} 
