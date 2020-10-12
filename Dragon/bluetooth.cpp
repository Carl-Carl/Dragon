/*
 * @Author: your name
 * @Date: 2020-10-11 09:07:03
 * @LastEditTime: 2020-10-12 08:25:37
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
    if (Serial.available()) {
        char ch;
        while ((ch = Serial.read()) != 0x80 && ch != EOF);
        
        if (ch == EOF)
            return;
        
        // 模式转换命令
        if ((ch = Serial.read()) == 0x80) {
            ch = Serial.read();
            if (0 <= ch && ch <= 2) {
                Modes = (MODE_FLAG)ch;
            }
        } // 遥控模式之下，收到命令
        else if ((ch = Serial.read()) == 0x81 && Modes == REMOTE_FLAG) {
            ch = Serial.read();    
            if (0 <= ch && ch <= 5)
                Order = (orders)ch;
        }

        while (Serial.read() != EOF);
    }
}

bluetooth::bluetooth()
{
    Modes = REMOTE_FLAG;
    Serial.begin(9600);
    Serial.println("bluetooth OK");
    Timer1.attachInterrupt(signal, 50000);  // 50ms 检查一次命令
}
