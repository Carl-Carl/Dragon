/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:26
 * @LastEditTime: 2020-10-19 08:06:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.cpp
 */
#include "remote.h"

remote::remote(motor &_control, u8 _shoot_pin) : control(_control), shoot_pin(_shoot_pin)
{
    Order = wait;
    shootgun.attach(shoot_pin);
}

void remote::fire()
{

    shootgun.write(45);
    delay(500);

    shootgun.write(135);
    delay(500);
    
}

void remote::mode()
{
    Order = wait;
    digitalWrite(shoot_pin, LOW);
    
    while (Modes == REMOTE_FLAG) {
        switch (Order) {
        case forward:
            control.forward(ANALOG_MAX, ANALOG_MAX);
            break;

        case backward:
            control.backward();
            break;

        case left:
            control.turn_left(ANALOG_MAX);
            break;

        case right:
            control.turn_right(ANALOG_MAX);
            break;

        case brake:
            control.brake();
            break;

        case shoot:
            fire();
            break;
        }
        
        delay(50);
    }
} 
