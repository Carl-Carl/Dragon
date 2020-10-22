/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:26
 * @LastEditTime: 2020-10-22 21:37:36
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
    delay(140);
    
    shootgun.write(0);
    delay(140);
    shootgun.detach();
    Timer1.attachInterrupt(signal, 50000);
}

static int SPEED = ANALOG_MAX;


void remote::mode()
{
    Order = wait;
    
    while (Modes == REMOTE_FLAG) {
        switch (Order) {
        case forward:
            Serial.println("for");
            control.forward(SPEED, SPEED);
            break;

        case backward:
            control.backward();
            break;

        case left:
            control.turn_left(SPEED);
            break;

        case right:
            control.turn_right(SPEED);
            break;

        case brake:
            control.brake();
            break;

        case shoot:
            fire();
            break;
        case up:
            SPEED += 5;
            break;
        case down:
            SPEED -= 5;
            break;
        }

        Order = wait;
        delay(50);
    }
} 
