/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-22 21:30:12
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Infrared.cpp
 */

#include <stdlib.h>
#include "Infrared.h"

Infrared::Infrared(motor &_control, u8 l_3, u8 l_2, u8 l_1, u8 r_1, u8 r_2, u8 r_3) : control(_control)
{
    
    this->left1 = l_1;
    this->left2 = l_2;
    this->left3 = l_3;
    this->right1 = r_1;
    this->right2 = r_2;
    this->right3 = r_3;

    pinMode(left1, INPUT);
    pinMode(left2, INPUT);
    pinMode(left3, INPUT);
    pinMode(right1, INPUT);
    pinMode(right2, INPUT);
    pinMode(right3, INPUT);
    
};

void Infrared::mode()
{

    while (Modes == INFRARED_FLAG)
    {

        if(digitalRead(left1) && digitalRead(right1))
        {
            control.forward(ANALOG_MAX, ANALOG_MAX);
        }

        else if(digitalRead(left2) || digitalRead(left3))
        {
            control.forward(ANALOG_SLOW, ANALOG_MAX);
        }

        else if(digitalRead(right2) || digitalRead(right3))
        {
            control.forward(ANALOG_MAX, ANALOG_SLOW);
        }

        control.brake();
        delay(300);

    }
    control.brake();
    delay(50);
};

bool Infrared::canStop()
{
    if( digitalRead(left1)== HIGH && 
        digitalRead(left2)== HIGH && 
        digitalRead(left3) == HIGH && 
        digitalRead(right1)== HIGH &&
        digitalRead(right2)== HIGH &&
        digitalRead(right3) == HIGH )
    {
        return true;
    }

    return false;
}
