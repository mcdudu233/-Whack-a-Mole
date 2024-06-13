//
// Created by dudu233 on 2024/6/11.
//

#ifndef WHACK_A_MOLE_GAME_H
#define WHACK_A_MOLE_GAME_H

#include "mole.h"
#include "thread"
#include "vector"

// 游戏难度
typedef enum { EASY,
               NORMAL,
               HARD } Difficulty;

// 地鼠洞的结构体
typedef struct {
    int x;
    int y;
    int width;
    int height;
    mole mole;
} Hole;

class game {
private:
    unsigned short level;                // 当前关卡等级
    Difficulty difficulty;               // 游戏难度
    unsigned int score;                  // 当前得分
    unsigned int time;                   // 剩余时间
    unsigned int moles;                  // 当前出现的地鼠数
    std::vector<std::vector<Hole>> holes;// 当前关卡地鼠洞的二维数组
    bool destroyed;                      // 是否已经销毁
    std::thread *moleThread;
    std::thread *hitThread;
    std::thread *hammerThread;
    std::thread *scoreThread;
    std::thread *endThread;

private:
    void
    delay(int milliseconds);    // 延时函数
    void spawnHoles();          // 初始化地鼠洞
    void spawnMoles();          // 随机生成地鼠
    void hitListener();         // 判断是否击中地鼠
    void hammerListener();      // 跟踪锤子
    void scoreListener();       // 顶部数据显示
    void endListener();         // 等待游戏时间结束
    float getDifficultyFactor();// 根据关卡等级和难度获得难度因子

public:
    game(unsigned short level, Difficulty diff);// 构造函数
    ~game();                                    // 析构函数
    void destroy();                             // 关闭这局游戏
    void startNewLevel();                       // 开始新关卡
    unsigned int getScore() const;              // 获取当前得分
    unsigned short getLevel() const;            // 获取当前关卡等级
    void increaseLevel();                       // 增加关卡等级
};


#endif//WHACK_A_MOLE_GAME_H
