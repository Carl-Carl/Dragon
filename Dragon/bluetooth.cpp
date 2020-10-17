/*
 * @Author: your name
 * @Date: 2020-10-11 09:07:03
 * @LastEditTime: 2020-10-17 08:32:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\bluetooth.cpp
 */
#include "bluetooth.h"

/*
 * 蓝牙信号接收-中断服务函数
 */
static void signal()
{
    char ch = Serial.read();

    if (ch != EOF) {
        if ('0' <= ch <= '6' && Modes == REMOTE_FLAG)
            Order = (orders)(ch - '0');
        else if ('7' <= ch && ch <= '9')
            Modes = (MODE_FLAG)(ch - '7');

        while (Serial.read() != EOF);
    }
}

bluetooth::bluetooth(int rate)
{
    Serial.begin(rate);
    delay(10);
    Timer1.attachInterrupt(signal, 50000);  // 50ms 检查一次命令
}
