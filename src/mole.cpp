//
// Created by dudu233 on 2024/5/26.
//

#include "mole.h"
#include "debug.h"
#include "graphics.h"
#include "random"
#include "window.h"

mole::mole() {

    this->x = rand() % (WINDOW_WIDTH);
    this->y = rand() % (WINDOW_HEIGHT);
    this->visible = false;
    debug("new mole in " + std::to_string(x) + "x" + std::to_string(y));
}

mole::mole(int x, int y) {
    this->x = x;
    this->y = y;
    this->visible = false;
    debug("new mole in " + std::to_string(x) + "x" + std::to_string(y));
}

bool mole::show() {
    this->visible = true;
    setfillcolor(BROWN);
    fillrectangle(this->x, this->y, this->x + 30, this->y + 30);
    debug("show mole in " + std::to_string(this->x) + "x" + std::to_string(this->y));
    return true;
}

bool mole::isShowed() {
    return this->visible;
}

int mole::getX() const {
    return this->x;
}

int mole::getY() const {
    return this->y;
}

bool mole::setX(int x) {
    this->x = x;
    return true;
}

bool mole::setY(int y) {
    this->y = y;
    return true;
}
