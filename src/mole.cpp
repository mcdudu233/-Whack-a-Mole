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
    this->speed = 3.0F;
    this->visible = false;
    debug("new mole in " + std::to_string(x) + "x" + std::to_string(y));
}

mole::mole(int x, int y) {
    this->x = x;
    this->y = y;
    this->speed = 3.0F;
    this->visible = false;
    debug("new mole in " + std::to_string(x) + "x" + std::to_string(y));
}

mole::~mole() {
    // 释放内存
    delete this->last;
}

void mole::delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// 探头并且缩回去
void mole::comeAndBack() {
    this->visible = true;
    if (this->last == nullptr) {
        this->last = new IMAGE;
    } else {
        putimage(this->x, this->y - 20, this->last);
    }
    getimage(this->last, this->x, this->y - 20, 100, 70);

    putImage(this->x, this->y, IMG_MOLE1);
    delay(80);
    putimage(this->x, this->y - 20, this->last);
    putImage(this->x, this->y - 5, IMG_MOLE2);
    delay(80);
    putimage(this->x, this->y - 20, this->last);
    putImage(this->x, this->y - 10, IMG_MOLE3);
    delay(80);
    putimage(this->x, this->y - 20, this->last);
    putImage(this->x, this->y - 15, IMG_MOLE4);
    // 等待一定时间回缩
    delay((int) (this->speed * 1000.0F));
    if (this->visible) {
        putimage(this->x, this->y - 20, this->last);
        putImage(this->x, this->y - 10, IMG_MOLE3);
        delay(30);
        putimage(this->x, this->y - 20, this->last);
        putImage(this->x, this->y - 5, IMG_MOLE2);
        delay(30);
        putimage(this->x, this->y - 20, this->last);
        putImage(this->x, this->y, IMG_MOLE1);
        delay(30);
        putimage(this->x, this->y - 20, this->last);
    }
    this->visible = false;
}

void mole::hit() {
    this->visible = false;
    putImage(this->x, this->y - 5, IMG_MOLE5);
    delay(300);
    putimage(this->x, this->y - 20, this->last);
    delay(1000);
    putimage(this->x, this->y - 20, this->last);
}

bool mole::show() {
    delay(500);
    debug("show mole in " + std::to_string(this->x) + "x" + std::to_string(this->y));
    // 创建探头并且回缩线程
    std::thread listen(&mole::comeAndBack, this);
    listen.detach();
    return true;
}

bool mole::isHited(int x, int y) {
    if (this->visible) {
        if (this->x <= x && x <= this->x + 80 && this->y <= y && y <= this->y + 50) {
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
