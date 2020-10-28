/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-10-28 13:52:58
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

    pinMode(left1, INPUT);
    pinMode(left2, INPUT);
    pinMode(left3, INPUT);
    pinMode(right1, INPUT);
    pinMode(right2, INPUT);
    pinMode(right3, INPUT);
    
};

void Infrared::mode()
{

    while (Modes == INFRARED_FLAG && (Serial.println(Modes) || 1))
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
            control.turn_left(ANALOG_SLOW);  //left
            if(digitalRead(left1) == HIGH && digitalRead(right1) == HIGH)
            {
                control.brake();
                delay(50); 
            }
        }

        if(leftsum < rightsum)
        {
            control.turn_right(ANALOG_SLOW);  //right
            if(digitalRead(left1) == HIGH && digitalRead(right1) == HIGH)
            {
                control.brake();
                delay(50); 
            }
        }
    }
    
    control.brake();
    delay(50);
}

/*
 * 0: b/w(infrared)
 * 1: b(stop)
 * 2: w(voice)
*/
int Infrared::canStop()
{
    if( digitalRead(left1) == LOW && 
        digitalRead(left2) == LOW && 
        digitalRead(left3) == LOW && 
        digitalRead(right1) == LOW &&
        digitalRead(right2) == LOW &&
        digitalRead(right3) == LOW )
    {
        return 2;
    }
    else if( digitalRead(left1) == HIGH && 
            digitalRead(left2) == HIGH && 
            digitalRead(left3) == HIGH && 
            digitalRead(right1) ==HIGH &&
            digitalRead(right2) == HIGH &&
            digitalRead(right3) == HIGH )
    {
        return 1;
    }

    return 0;    
}
