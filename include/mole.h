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
    bool hited;  // �Ƿ񱻻���
    IMAGE last;  //��һ��ͼƬ

private:
    void delay(int milliseconds);// ��ʱ����
    void comeAndBack();          // ̽ͷ������ȥ
    void hit();                  // ��������Ч

public:
    mole();
    mole(int x, int y);
    ~mole();
    int getX() const;
    int getY() const;
    bool setX(int x);
    bool setY(int y);
    bool show();               // ����̽ͷ
    bool isShowed();           // �����Ƿ�̽ͷ
    bool isHited(int x, int y);// �Ƿ���е���
    void destroy();            // ����
};


#endif//WHACK_A_MOLE_MOLE_H
