//
// Created by dudu233 on 2024/5/26.
//

#ifndef WHACK_A_MOLE_MOLE_H
#define WHACK_A_MOLE_MOLE_H


class mole {
private:
    unsigned int x;
    unsigned int y;
    bool visible;// ÊÇ·ñ³öÏÖ

public:
    mole();
    mole(int x, int y);
    int getX() const;
    int getY() const;
    bool setX(int x);
    bool setY(int y);
    bool show();
    bool isShowed();
};


#endif//WHACK_A_MOLE_MOLE_H
