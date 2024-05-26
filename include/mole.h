//
// Created by dudu233 on 2024/5/26.
//

#ifndef WHACK_A_MOLE_MOLE_H
#define WHACK_A_MOLE_MOLE_H


class mole {
private:
    int x;
    int y;
    bool visible;

public:
    mole();
    mole(int x, int y);
    int getX() const;
    int getY() const;
    bool setX(int x);
    bool setY(int y);
    bool show();
};


#endif//WHACK_A_MOLE_MOLE_H
