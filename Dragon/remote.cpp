/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:26
 * @LastEditTime: 2020-10-11 10:37:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.cpp
 */
#include "remote.h"

remote::remote(motor &_control) : control(_control)
{
    Order = wait;
}

void remote::mode()
{
    while (Modes == REMOTE_FLAG) {
        switch (Order) {
        case forward:
            control.forward();
            break;

        case backward:
            control.backward();
            break;

        case left:
            control.turn_left();
            break;

        case right:
            control.turn_right();
            break;

        case brake:
            control.brake();
            break;
        }

        Order = wait;
        delay(50);
    }
} 
