/*
 * @Author: your name
 * @Date: 2020-10-10 15:45:14
 * @LastEditTime: 2020-10-10 16:05:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \Dragon\remote.h
 */
#ifndef REMOTE
#define REMOTE

/*
 * 0 : brake
 * 1 : forward
 * 2 : left
 * 3 : right
 */
enum remote_modes {
    wait        =   0,
    forward     =   1,
    backward    =   2,
    left        =   3,
    right       =   4,
    brake       =   5,
} remote_mode;

class remote
{
private:
    ;
public:
    remote();
    // 启动遥控模式
    void mode();
};




#endif // !REMOTE