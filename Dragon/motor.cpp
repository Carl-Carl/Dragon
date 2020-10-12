/*
 * @Author: XHM
 * @Date: 2020-10-10 12:26:44
 * @LastEditTime: 2020-10-12 10:13:59
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

void motor::wait()
{
    analogWrite(le, 0);
    analogWrite(re, 0);
}

void motor::forward(u8 speed)
{
    analogWrite(le, speed);
    analogWrite(re, speed);
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

void motor::turn_left(u8 speed)
{
    analogWrite(le, speed >> 2);
    analogWrite(re, speed);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
}

void motor::turn_right(u8 speed)
{
    analogWrite(le, speed);
    analogWrite(re, speed >> 2);
    digitalWrite(l1, LOW);
    digitalWrite(l2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, HIGH);
}

void motor::brake()
{
    analogWrite(le, 255);
    analogWrite(re, 255);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
}
