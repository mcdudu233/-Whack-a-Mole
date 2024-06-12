//
// Created by dudu233 on 2024/6/11.
//

#ifndef WHACK_A_MOLE_GAME_H
#define WHACK_A_MOLE_GAME_H

#include "mole.h"
#include "vector"

// 游戏难度
typedef enum { EASY,
               NORMAL,
               HARD } Difficulty;

// 地鼠洞的结构体
typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    mole mole;
} Hole;

class game {
private:
    unsigned short level;                // 当前关卡等级
    Difficulty difficulty;               // 游戏难度
    unsigned int score;                  // 当前得分
    std::vector<std::vector<Hole>> holes;// 当前关卡地鼠洞的二维数组
private:
    void initializeHoles();     // 初始化地鼠洞
    void spawnMoles();          // 随机生成地鼠
    float getDifficultyFactor();// 根据关卡等级和难度获得难度因子
public:
    game(unsigned short level, Difficulty diff); // 构造函数
    ~game();                                     // 析构函数
    void startNewLevel();                        // 开始新关卡
    void hitMole(unsigned int x, unsigned int y);// 击打地鼠
    unsigned int getScore() const;               // 获取当前得分
    unsigned short getLevel() const;             // 获取当前关卡等级
    void increaseLevel();                        // 增加关卡等级
};


#endif//WHACK_A_MOLE_GAME_H
