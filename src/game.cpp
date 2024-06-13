//
// Created by dudu233 on 2024/6/11.
//

#include "game.h"
#include "debug.h"
#include "easyx.h"
#include "graphics.h"
#include "resource.h"
#include "thread"
#include "window.h"

game::game(unsigned short level, Difficulty diff) : level(level), difficulty(diff), score(0), moles(0), destroyed(false) {
    // 加载图片资源
    initResource();

    // 生成地鼠洞和地鼠
    spawnHoles();
    std::thread moleListener(&game::spawnMoles, this);
    moleListener.detach();
    std::thread hitListener(&game::hitMoles, this);
    hitListener.detach();

    // 跟踪锤子
    std::thread hammerListener(&game::hammerListener, this);
    hammerListener.detach();
}

game::~game() {
    // 关闭所有线程
    this->destroyed = true;
    // 如果有需要清理的资源，在这里进行清理
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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// 随机生成地鼠
void game::hitMoles() {
    MOUSEMSG m;
    int x, y;
    while (!destroyed) {
        m = GetMouseMsg();
        if (m.mkLButton) {
            x = m.x;
            y = m.y;
            for (auto &row: holes) {
                for (auto &hole: row) {
                    if (hole.mole.isHited(x, y)) {
                        debug("mole hited");
                        // 每击中一个地鼠得5分
                        score += 5;
                    }
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

void game::destory() {
    this->destroyed = true;
}
