/*
 * @Author: your name
 * @Date: 2020-10-09 10:32:24
 * @LastEditTime: 2020-10-10 12:25:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Voice\voice\voice.ino
 */
#ifndef VOICE
#define VOICE

#include <stdlib.h>

/*
 * DIST_INFO 对象用于存储超声波回传的信息
 * 成员 front, left 和 right 分别保存距离三个方向墙壁的距离，单位：cm。
*/
typedef struct DIST_INFO {
  u16 front;
  u16 left;
  u16 right;
} DIST_INFO;

/*
 * dist 对象用于初始化超声波测距系统和进行超声波测距
 * dist() ：构造函数，会完成引脚的初始化工作
 * get_dist() ：会测量好距离，并打包成 DIST_INFO 对象
*/
class dist {
  u8 send_pin;
  u8 front_pin;
  u8 left_pin;
  u8 right_pin;
  
public:
  dist(u8 _send_pin, u8 _front_pin, u8 _left_pin, u8 _right_pin) {
    this->send_pin = _send_pin;
    this->front_pin = _front_pin;
    this->left_pin = _left_pin;
    this->right_pin = _right_pin;

    pinMode(send_pin, OUTPUT);
    digitalWrite(send_pin, LOW);

    pinMode(front_pin, INPUT);
    pinMode(left_pin, INPUT);
    pinMode(right_pin, INPUT);
  }

  /* return the distance with cm */
  void get_dist(DIST_INFO &distance) {
    
    u16 *a[3] = {&distance.front, &distance.left, &distance.right};
    u8 ports[3] = {front_pin, left_pin, right_pin};
    u16 temp[8];

    for (u8 i = 0; i < 3; ++i) {
      // 取平均值
      for (u8 j = 0; j < 8; ++j) {
        // send begin order
        digitalWrite(send_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(send_pin, LOW);

        temp[j] = pulseIn(ports[i], HIGH, 180000)/59;
      }

      // sort and get the average
      qsort(temp, 8, sizeof(u16), [](const void *a, const void *b) {return (int)(*(int*)a < *(int*)b);});
      
      *a[i] = 0;
      for (u8 j = 2; j < 6; ++j)
        *a[i] += temp[j];
      
      *a[i] >>= 2;
    }
  }
};

#endif
