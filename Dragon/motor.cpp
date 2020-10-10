/*
 * @Author: XHM
 * @Date: 2020-10-10 12:26:44
 * @LastEditTime: 2020-10-10 14:48:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\motor.cpp
 */
#include "motor.h"

motor::motor(u8 _le, u8 _re, u8 _l1, u8 _l2, u8 _r1, u8 _r2)
: le(_le), re(_re), l1(_l1), l2(_l2), r1(_r1), r2(_r2)
{
    pinMode(l1, OUTPUT);
    pinMode(l2, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(r2, OUTPUT);

    digitalWrite(LEFT_1, LOW);
    digitalWrite(LEFT_2, LOW);
    digitalWrite(RIGHT_1, LOW);
    digitalWrite(RIGHT_2, LOW);
}

void motor::mode()
{
    analogWrite(LEFT_E, ANALOG_MAX);
    analogWrite(RIGHT_E, ANALOG_MAX);
    digitalWrite(LEFT_2, HIGH);
    digitalWrite(RIGHT_2, HIGH);
}

void motor::forward()
{
    ;
}

void motor::turn_left()
{
    ;
}

void motor::turnright()
{
    ;
}