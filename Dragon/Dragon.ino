/*
 * @Author: your name
 * @Date: 2020-10-09 11:16:31
 * @LastEditTime: 2020-10-09 21:09:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\Dragon.ino
 */
#include "Interface.h"

dist distance(VOICE_SEND_PIN, FRONT_PIN, LEFT_PIN, RIGHT_PIN);
DIST_INFO v_dist;

void setup () {
    Serial.begin(9600);
}

void loop() {
    distance.get_dist(v_dist);
    Serial.print("front: ");
    Serial.println(v_dist.front);

    Serial.print("left: ");
    Serial.println(v_dist.left);

    Serial.print("right: ");
    Serial.println(v_dist.right);
    Serial.println("");
    delay(2000);
}