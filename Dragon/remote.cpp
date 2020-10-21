/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:26
 * @LastEditTime: 2020-10-20 20:57:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.cpp
 */
#include "remote.h"
#include "Timerone.h"

remote::remote(motor &_control, Servo &shoot_gun, void sig()) : control(_control), shootgun(shoot_gun), signal(sig)
{
    Order = wait;
    //shootgun.attach(11);
}

void remote::fire()
{
    shootgun.attach(4);
    delay(10);
    
    shootgun.write(90);
    delay(170);
    
    shootgun.write(0);
    delay(170);
    shootgun.detach();
    Timer1.attachInterrupt(signal, 50000);
}

void remote::mode()
{
    Order = wait;
    
    while (Modes == REMOTE_FLAG) {
        switch (Order) {
        case forward:
            Serial.println("for");
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

        Order = wait;
        delay(50);
    }
} 
