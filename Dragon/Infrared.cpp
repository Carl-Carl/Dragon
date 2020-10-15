/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-14 19:34:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Infrared.cpp
 */

#include <stdlib.h>
#include "Infrared.h"

Infrared::Infrared(motor &_control, u8 l_4, u8 l_3, u8 l_2, u8 l_1, u8 r_1, u8 r_2, u8 r_3, u8 r_4):control(_control)
{
    this->left1 = l_1;
    this->left2 = l_2;
    this->left3 = l_3;
    this->left4 = l_4;
    this->right1 = r_1;
    this->right2 = r_2;
    this->right3 = r_3;
    this->right4 = r_4;

    pinMode(l_1, INPUT);
    pinMode(l_2, INPUT);
    pinMode(l_3, INPUT);
    pinMode(l_4, INPUT);
    pinMode(r_1, INPUT);
    pinMode(r_2, INPUT);
    pinMode(r_3, INPUT);
    pinMode(r_4, INPUT);
};

void Infrared::mode()
{

    while(Modes == INFRARED_FLAG)
    {
        Infrared_Info signal;
        signal.left[0] = digitalRead(left1);
        signal.left[1] = digitalRead(left2);
        signal.left[2] = digitalRead(left3);
        signal.left[3] = digitalRead(left4);
        signal.right[0] = digitalRead(right1);
        signal.right[1] = digitalRead(right2);
        signal.right[2] = digitalRead(right3);
        signal.right[3] = digitalRead(right4);
        
        if(signal.left[0] == HIGH && signal.left[1] == HIGH && signal.right[0] == HIGH && signal.right[1] == HIGH)
        {
            control.forward(60, 60);
            Serial.println("go forward\n");
        }

        u8 leftsum = 0, rightsum = 0;
        for(u8 i = 0; i < 4 ; i++)
        {
            if(signal.left[i] == HIGH) leftsum += 1;
            if(signal.right[i] == HIGH) rightsum += 1;
        }

        // Serial.println(leftsum);
        // Serial.println(rightsum);

        if(leftsum > rightsum)
        {
            control.forward(55, 20);
            // Serial.println("turn right\n");
        }

        if(leftsum == rightsum)
        {
            control.forward(60, 60);
            // Serial.println("go forward\n");
        }

        if(rightsum > leftsum)
        {
            control.forward(20, 55);
            // Serial.println("turn left\n");
        }
    }

    control.brake();
    delay(50);
};
