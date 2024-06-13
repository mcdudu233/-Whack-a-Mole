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
    float speed; // ���󶯻����ٶ�
    bool visible;// �Ƿ����
    IMAGE *last; //��һ��ͼƬ

private:
    void initImage();

public:
    mole();
    ~mole();
    mole(int x, int y);
    int getX() const;
    int getY() const;
    bool setX(int x);
    bool setY(int y);
    bool show();
    bool isShowed();
};


#endif//WHACK_A_MOLE_MOLE_H
