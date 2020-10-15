/*
 * @Author: your name
 * @Date: 2020-10-11 09:07:03
 * @LastEditTime: 2020-10-14 18:57:56
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
//  
  
    if (Serial.available()) {

        char ch = Serial.read();
        if (0 <= ch && ch <= 6) {
            Order = (orders)ch;
            delay(5000);
            Serial.println(ch);
        }

        while (Serial.read() != EOF);
    }
}

bluetooth::bluetooth(int rate)
{
    Serial.begin(rate);
    delay(10);
    Timer1.attachInterrupt(signal, 50000);  // 50ms 检查一次命令
}
