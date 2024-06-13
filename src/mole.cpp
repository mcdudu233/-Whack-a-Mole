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
}

mole::mole(int x, int y) {
    this->x = x;
    this->y = y;
    this->speed = 3.0F;
    this->visible = false;
    this->hited = false;
    getimage(&this->last, this->x, this->y - 20, 100, 70);
    debug("new mole in " + std::to_string(x) + "x" + std::to_string(y));
}

mole::~mole() {
    // 释放内存
}

// 探头并且缩回去
void mole::comeAndBack() {
    this->visible = true;
    this->hited = false;
    putimage(this->x, this->y - 20, &this->last);

    putImage(this->x, this->y, IMG_MOLE1);
    delay(50);
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y - 5, IMG_MOLE2);
    } else {
        return;
    }
    delay(50);
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y - 10, IMG_MOLE3);
    } else {
        return;
    }
    delay(50);
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y - 15, IMG_MOLE4);
    } else {
        return;
    }
    // 等待一定时间回缩
    delay((int) (this->speed * 1000.0F));
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y - 10, IMG_MOLE3);
    } else {
        return;
    }
    delay(30);
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y - 5, IMG_MOLE2);
    } else {
        return;
    }
    delay(30);
    if (!this->hited) {
        putimage(this->x, this->y - 20, &this->last);
        putImage(this->x, this->y, IMG_MOLE1);
        delay(30);
        putimage(this->x, this->y - 20, &this->last);
    } else {
        return;
    }
    this->visible = false;
}

void mole::hit() {
    this->hited = true;
    putimage(this->x, this->y - 20, &this->last);
    putImage(this->x, this->y - 5, IMG_MOLE5);
    delay(500);
    putimage(this->x, this->y - 20, &this->last);
    this->visible = false;
}

bool mole::show() {
    if (!this->visible) {
        debug("show mole in " + std::to_string(this->x) + "x" + std::to_string(this->y));
        // 创建探头并且回缩线程
        std::thread listen(&mole::comeAndBack, this);
        listen.detach();
    }
    return true;
}

bool mole::isHited(int x, int y) {
    if (this->visible) {
        if (this->x <= x && x <= this->x + 80 && this->y - 30 <= y && y <= this->y + 50) {
            std::thread listen(&mole::hit, this);
            listen.detach();
            return true;
        }
    }
    return false;
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

void mole::destroy() {
    this->hited = true;
}