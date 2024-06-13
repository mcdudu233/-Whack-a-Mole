//
// Created by dudu233 on 2024/5/26.
//

#ifndef WHACK_A_MOLE_MOLE_H
#define WHACK_A_MOLE_MOLE_H
#include "easyx.h"

class mole {
private:
    int x;
    int y;
    float speed; // 地鼠动画的速度
    bool visible;// 是否出现
    bool hited;  // 是否被击中
    IMAGE last;  //上一个图片

private:
    void delay(int milliseconds);// 延时函数
    void comeAndBack();          // 探头和缩回去
    void hit();                  // 被击中特效

public:
    mole();
    mole(int x, int y);
    ~mole();
    int getX() const;
    int getY() const;
    bool setX(int x);
    bool setY(int y);
    bool show();               // 地鼠探头
    bool isShowed();           // 地鼠是否探头
    bool isHited(int x, int y);// 是否打中地鼠
    void destroy();            // 销毁
};


#endif//WHACK_A_MOLE_MOLE_H
