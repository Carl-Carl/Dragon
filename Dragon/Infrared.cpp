/*
 * @Author: your name
 * @Date: 2020-10-13 08:29:55
 * @LastEditTime: 2020-11-01 13:47:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Infrared.cpp
 */

#include <stdlib.h>
#include "Infrared.h"

u8 last = 0; //0为之前为前进，1为拐弯

Infrared::Infrared(motor &_control, u8 l_3, u8 l_2, u8 l_1, u8 r_1, u8 r_2, u8 r_3, u8 mid) : control(_control)
{
    
    this->left1 = l_1;
    this->left2 = l_2;
    this->left3 = l_3;
    this->right1 = r_1;
    this->right2 = r_2;
    this->right3 = r_3;
    this->Mid = mid;

    pinMode(left1, INPUT);
    pinMode(left2, INPUT);
    pinMode(left3, INPUT);
    pinMode(right1, INPUT);
    pinMode(right2, INPUT);
    pinMode(right3, INPUT);
    pinMode(Mid, OUTPUT);
    digitalWrite(mid, LOW);
    pinMode(Mid, INPUT);
    
};

void Infrared::mode()
{
    while (Modes == INFRARED_FLAG) {
        u8 leftsum = 0, rightsum = 0;
        leftsum +=  digitalRead(left2) + digitalRead(left3);
        rightsum +=  digitalRead(right2) + digitalRead(right3);

        if(leftsum > rightsum)
        {
            if (leftsum == 2) {
                control.backward();
                delay(22);
                
                control.turn_left(ANALOG_MAX + 40);
                last = 0;
                while (digitalRead(right3) || digitalRead(left2)) {
                    ++last;
                    delay(10);
                    Modes = INFRARED_FLAG;
                }

                if (last >= 10) {
                    control.brake();
                    delay(30);
                }
            } else {
                control.turn_left(ANALOG_MAX + 40);
            }
 
            last = 0;
        }
        else if(leftsum < rightsum)
        {
            if (rightsum == 2) {
                control.backward();
                delay(22);
                
                control.turn_right(ANALOG_MAX + 40);
                last = 0;
                while (digitalRead(right2) || digitalRead(left3)) {
                    ++last;
                    delay(10);
                    Modes = INFRARED_FLAG;
                }

                if (last >= 10) {
                    control.brake();
                    delay(30);
                }
            } else {
                control.turn_right(ANALOG_MAX + 40);
            }
            
            last = 0;
        } else {              //if(digitalRead(left1) == HIGH || digitalRead(right1) == HIGH) {
            ++last;
            if (last >= 22)
                control.forward(ANALOG_MAX-20, ANALOG_MAX-20);
            else
                control.forward(ANALOG_MAX, ANALOG_MAX);
        }

        delay(10);
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
        digitalRead(right3) == LOW &&
        digitalRead(MID) == LOW)
    {
        return 2;
    }
    else if( digitalRead(left1) == HIGH && 
            digitalRead(left2) == HIGH && 
            digitalRead(left3) == HIGH && 
            digitalRead(right1) ==HIGH &&
            digitalRead(right2) == HIGH &&
            digitalRead(right3) == HIGH &&
            digitalRead(MID) == HIGH)
    {
        return 1;
    }

    return 0;    
}
