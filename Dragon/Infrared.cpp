/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-19 21:40:05
 * @LastEditors: Please set LastEditors
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

    pinMode(l_1, INPUT);
    pinMode(l_2, INPUT);
    pinMode(l_3, INPUT);
    pinMode(r_1, INPUT);
    pinMode(r_2, INPUT);
    pinMode(r_3, INPUT);
    
};

void Infrared::mode()
{

    while (Modes == INFRARED_FLAG)
    {
        Infrared_Info signal;
        signal.left[0] = digitalRead(left1);
        signal.left[1] = digitalRead(left2);
        signal.left[2] = digitalRead(left3);
        signal.right[0] = digitalRead(right1);
        signal.right[1] = digitalRead(right2);
        signal.right[2] = digitalRead(right3);
        
        if (signal.left[0] == HIGH && signal.right[0] == HIGH)
        {
            control.forward(SPEED, SPEED);
        }

        u8 leftsum = 0, rightsum = 0;
        for (u8 i = 0; i < 3; i++)
        {
            if (signal.left[i] == HIGH)
                leftsum += 1;
            if (signal.right[i] == HIGH)
                rightsum += 1;
        }
        if (leftsum == rightsum)
        {
            control.forward(ANALOG_MAX, ANALOG_MAX);
            // Serial.println("go forward\n");
        } else {
            if (leftsum > rightsum)
            {
                control.forward(ANALOG_MAX, ANALOG_SLOW);
                // Serial.println("turn right\n");
            }

            if (rightsum > leftsum)
            {
                control.forward(ANALOG_SLOW ,ANALOG_MAX);
                // Serial.println("turn left\n");
            }
        }
    }

    control.brake();
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