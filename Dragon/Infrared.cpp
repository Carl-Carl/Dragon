/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-24 21:44:11
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
        if(digitalRead(left1) == HIGH && digitalRead(right1) == HIGH)
        {
            control.forward(ANALOG_MAX, ANALOG_MAX);    
        }

        u8 leftsum = 0, rightsum = 0;
        leftsum += digitalRead(left1) + digitalRead(left2) + digitalRead(left3);
        rightsum += digitalRead(right1) + digitalRead(right2) + digitalRead(right3);

        if(leftsum > rightsum)
        {
            control.turn_left(ANALOG_SLOW);
        }

        if(leftsum < rightsum)
        {
            control.turn_right(ANALOG_SLOW);
        }
    }
    
    control.brake();
    delay(50);
}

bool Infrared::canStop()
{
    if( digitalRead(left1) == LOW && 
        digitalRead(left2) == LOW && 
        digitalRead(left3) == LOW && 
        digitalRead(right1) == LOW &&
        digitalRead(right2) == LOW &&
        digitalRead(right3) == LOW )
    {
        return true;
    }

    return false;
}
