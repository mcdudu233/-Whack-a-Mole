//
// Created by dudu233 on 2024/6/11.
//

#include "game.h"
#include "debug.h"
#include "easyx.h"
#include "graphics.h"
#include "resource.h"
#include "window.h"

void game::delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

IMAGE tmp_4;
game::game(unsigned short level, Difficulty diff) : level(level), difficulty(diff), score(0), time(10), moles(0), destroyed(false) {
    // 加载图片资源
    initResource();
    getimage(&tmp_4,160,0,100,120);
    // 生成地鼠洞和地鼠
    spawnHoles();
    moleThread = new std::thread(&game::spawnMoles, this);
    hitThread = new std::thread(&game::hitListener, this);

    // 跟踪锤子
    hammerThread = new std::thread(&game::hammerListener, this);

    // 数据刷新
    scoreThread = new std::thread(&game::scoreListener, this);

    // 关卡结束
    endThread = new std::thread(&game::endListener, this);
}

game::~game() {
    destroy();
}

// 根据关卡等级和难度获得难度因子
float game::getDifficultyFactor() {
    float factor = this->level;
    if (factor > 100) {
        factor /= 4.0F;
    } else if (factor > 50) {
        factor /= 3.0F;
    } else if (factor > 30) {
        factor /= 2.5F;
    } else if (factor > 20) {
        factor /= 2.0F;
    } else if (factor > 10) {
        factor /= 1.5F;
    } else if (factor > 5) {
        factor /= 1.3F;
    } else {
        factor /= 1.1F;
    }
    switch (this->difficulty) {
        case EASY:
            return factor * 0.8F;
        case NORMAL:
            return factor * 1.0F;
        case HARD:
            return factor * 1.3F;
        default:
            return -1;
    }
}

// 初始化地鼠洞
void game::spawnHoles() {
    float diff = getDifficultyFactor();// 获取难度因子
    // 根据难度计算行列
    unsigned int rows = 1 + (int) (diff / 5.0F);
    unsigned int cols = rows;
    unsigned int gapX = 40;
    unsigned int gapY = 30;

    for (int i = 0; i < rows; i++) {
        std::vector<Hole> hole(cols);
        holes.push_back(hole);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = WINDOW_WIDTH / 2 - (rows * 100 + (rows - 1) * gapX) / 2 + i * (100 + gapX);
            int y = WINDOW_HEIGHT / 2 - (cols * 50 + (cols - 1) * gapY) / 2 + j * (50 + gapY);
            putImage(x, y, IMG_HOLE);
            holes[i][j] = {x, y, 100, 50, mole(x + 30, y)};
        }
    }
}

// 随机生成地鼠
void game::spawnMoles() {
    MOUSEMSG m;
    int x, y;
    while (!destroyed) {
        for (auto &row: holes) {
            for (auto &hole: row) {
                if (rand() < (int) (getDifficultyFactor() * 100.0F)) {
                    debug("show mole");
                    hole.mole.show();
                }
            }
        }
        delay(50);
    }
}

// 随机生成地鼠
void game::hitListener() {
    MOUSEMSG m;
    int x, y;
    while (!destroyed) {
        debug("run1");
        m = GetMouseMsg();
        debug("run2");
        int width = getwidth();
        int height = getheight();
        x = ((m.x) * 800) / width;
        y = ((m.y) * 600) / height;
        for (auto &row: holes) {
            for (auto &hole: row) {
                if (m.mkLButton && hole.mole.isHited(x, y)) {
                    debug("mole hited, now score:" + std::to_string(this->score));
                    // 每击中一个地鼠得5分
                    score += 5;
                }
            }
        }
    }
}

// 监听锤子位置
void game::hammerListener() {
    IMAGE *tmp;
    MOUSEMSG m;
    int x, y, last_x, last_y;
    while (!destroyed) {
        m = GetMouseMsg();
        int width = getwidth();
        int height = getheight();
        x = ((m.x) * 800) / width - 50;
        y = ((m.y) * 600) / height - 50;

        // 还原之前的状态
        if (tmp == nullptr) {
            tmp = new IMAGE;
        } else {
            putimage(last_x, last_y, tmp);
        }
        // 保存之前的状态
        getimage(tmp, x, y, 100, 100);
        last_x = x;
        last_y = y;
        // 放置锤子
        if (m.mkLButton) {
            debug("hammer down.");
            putImage(x, y, IMG_HAMMER_DOWN);
        } else {
            putImage(x, y, IMG_HAMMER);
        }
    }
}

// 顶部数据显示
void game::scoreListener() {
    while (!destroyed) {
        putimage(160,0,&tmp_4);
        switch (this->difficulty) {
            case EASY: {
                settextstyle(30, 0, "楷体");
                settextcolor(BLACK);
                outtextxy(160, 130, "简单");
                break;
            }
            case NORMAL: {
                settextstyle(30, 0, "楷体");
                settextcolor(BLACK);
                outtextxy(160, 130, "普通");
                break;
            }
            case HARD: {
                settextstyle(30, 0, "楷体");
                settextcolor(BLACK);
                outtextxy(160, 130, "困难");
                break;
            }
        }  // 输出当前关卡
        settextstyle(30, 0, "楷体");
        settextcolor(BLACK);
        outtextxy(160, 10, std::to_string(this->level).c_str());
        // 输出剩余时间
        settextstyle(30, 0, "楷体");
        settextcolor(BLACK);
        outtextxy(160, 50, std::to_string(this->time).c_str());
        // 输出当前得分
        settextstyle(30, 0, "楷体");
        settextcolor(BLACK);
        outtextxy(160, 90, std::to_string(this->score).c_str());
        // 每隔100ms刷新一次
        delay(100);
    }
}


// 游戏时间
void game::endListener() {
    while (!destroyed) {
        // 每1s检测一次
        delay(1000);
        this->time--;
        debug("now time:" + std::to_string(this->time));
        if (time == 0) {
            // 本关结束了
            debug("level: " + std::to_string(this->level) + "ended");
            destroy();
            new game(++this->level, this->difficulty);
            break;
        }
    }
}

// 开始新关卡
void game::startNewLevel() {
    increaseLevel();
    spawnMoles();
}

// 获取当前得分
unsigned int game::getScore() const {
    return score;
}

// 获取当前关卡等级
unsigned short game::getLevel() const {
    return level;
}

// 增加关卡等级
void game::increaseLevel() {
    ++level;
}

void game::destroy() {
    this->destroyed = true;
    for (auto &row: holes) {
        for (auto &hole: row) {
            hole.mole.destroy();
        }
    }
    // 等待所有线程结束
    moleThread->join();
    hitThread->join();
    hammerThread->join();
    scoreThread->join();
    endThread->join();
}
