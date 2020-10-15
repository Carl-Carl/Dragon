/*
 * @Author: your name
 * @Date: 2020-10-11 09:07:03
 * @LastEditTime: 2020-10-15 21:50:03
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
    static char a[3], num_of_char = 0;
    
    if (Serial.available()) {
        while (Serial.available() && num_of_char <= 3) {
            a[num_of_char++] = Serial.read();
        }

        if (num_of_char >= 3) {
            num_of_char = 0;
            if (a[0] == 'm' && a[2] == 'e') {
                if ('0' <= a[1] && a[1] <= '2')
                    Modes = (MODE_FLAG)a[1];
            } else if (a[0] == 'o' && a[2] == 'e') {
                if ('0' <= a[1] && a[1] <= '6')
                    Order = (orders)a[1];
            }
            while (Serial.read() != EOF);
        }
    }
}

bluetooth::bluetooth(int rate)
{
    Serial.begin(rate);
    delay(10);
    Timer1.attachInterrupt(signal, 50000);  // 50ms 检查一次命令
}
