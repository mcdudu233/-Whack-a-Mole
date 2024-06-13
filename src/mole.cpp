//
// Created by dudu233 on 2024/5/26.
//

#include "mole.h"
#include "debug.h"
#include "graphics.h"
#include "random"
#include "resource.h"
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

mole::~mole() {
    // ÊÍ·ÅÄÚ´æ
    delete this->last;
}

bool mole::show() {
    debug("show mole in " + std::to_string(this->x) + "x" + std::to_string(this->y));
    this->visible = true;
    if (this->last == nullptr) {
        this->last = new IMAGE;
    } else {
        putimage(this->x, this->y, this->last);
    }
    getimage(this->last, this->x, this->y, 100, 50);
    putImage(this->x, this->y, IMG_MOLE1);
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
