/*
 * @Author: XHM
 * @Date: 2020-10-10 12:26:44
 * @LastEditTime: 2020-10-11 20:51:47
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

    brake();
}

void motor::forward()
{
    analogWrite(le, ANALOG_MAX);
    analogWrite(re, ANALOG_MAX);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
}

void motor::backward()
{
    analogWrite(le, ANALOG_MAX);
    analogWrite(re, ANALOG_MAX);
    digitalWrite(l1, HIGH);
    digitalWrite(l2, LOW);
    digitalWrite(r1, HIGH);
    digitalWrite(r2, LOW);
}

void motor::turn_left()
{
    analogWrite(le, ANALOG_SLOW);
    analogWrite(re, ANALOG_MAX);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
}

void motor::turn_right()
{
    analogWrite(le, ANALOG_MAX);
    analogWrite(re, ANALOG_SLOW);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
}

void motor::brake()
{
    analogWrite(le, ANALOG_MAX);
    analogWrite(re, ANALOG_MAX);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
}