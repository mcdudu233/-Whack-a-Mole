//
// Created by dudu233 on 2024/6/11.
//

#include "game.h"
#include "debug.h"
#include "window.h"

game::game(unsigned short level, Difficulty diff) : level(level), difficulty(diff), score(0) {
    initializeHoles();
    spawnMoles();
}

game::~game() {
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
void game::initializeHoles() {
    float diff = getDifficultyFactor();// 获取难度因子
    // 根据难度计算行列
    unsigned int rows = 1 + (int) (diff / 5);
    unsigned int cols = rows;
    unsigned int gapX = WINDOW_WIDTH / rows;
    unsigned int gapY = WINDOW_HEIGHT / cols;

    holes.resize(rows, std::vector<Hole>(cols));
    for (unsigned int i = 0; i < rows; i += gapX) {
        for (unsigned int j = 0; j < cols; j += gapY) {
            holes[i][j] = {i, j, 100, 100, mole(i, j)};
        }
    }
}

// 随机生成地鼠
void game::spawnMoles() {
    for (auto &row: holes) {
        for (auto &hole: row) {
            hole.mole.show();
        }
    }
}

// 开始新关卡
void game::startNewLevel() {
    increaseLevel();
    spawnMoles();
}

// 击打地鼠
void game::hitMole(unsigned int x, unsigned int y) {
    for (auto &row: holes) {
        for (auto &hole: row) {
            if (x >= hole.x && x < (hole.x + hole.width) &&
                y >= hole.y && y < (hole.y + hole.height)) {
                if (hole.mole.isShowed()) {
                    //                    hole.mole.isVisible = false;
                    score += 10;// 每击中一个地鼠得10分
                }
                return;
            }
        }
    }
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
#include "window.h"

game::game(unsigned short level, Difficulty diff) : level(level), difficulty(diff), score(0) {
    initializeHoles();
    spawnMoles();
}

game::~game() {
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
void game::initializeHoles() {
    float diff = getDifficultyFactor();// 获取难度因子
    // 根据难度计算行列
    unsigned int rows = 1 + (int) (diff / 5);
    unsigned int cols = rows;
    unsigned int gapX = WINDOW_WIDTH / rows;
    unsigned int gapY = WINDOW_HEIGHT / cols;

    holes.resize(rows, std::vector<Hole>(cols));
    for (unsigned int i = 0; i < rows; i += gapX) {
        for (unsigned int j = 0; j < cols; j += gapY) {
            holes[i][j] = {i, j, 100, 100, mole(i, j)};
        }
    }
}

// 随机生成地鼠
void game::spawnMoles() {
    for (auto &row: holes) {
        for (auto &hole: row) {
            hole.mole.show();
        }
    }
}

// 开始新关卡
void game::startNewLevel() {
    increaseLevel();
    spawnMoles();
}

// 击打地鼠
void game::hitMole(unsigned int x, unsigned int y) {
    for (auto &row: holes) {
        for (auto &hole: row) {
            if (x >= hole.x && x < (hole.x + hole.width) &&
                y >= hole.y && y < (hole.y + hole.height)) {
                if (hole.mole.isShowed()) {
                    //                    hole.mole.isVisible = false;
                    score += 10;// 每击中一个地鼠得10分
                }
                return;
            }
        }
    }
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