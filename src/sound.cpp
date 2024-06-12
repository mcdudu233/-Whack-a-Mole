//
// Created by dudu233 on 2024/6/8.
//

#include "sound.h"
#include "debug.h"
#include "graphics.h"
#include "mmsystem.h"
#include "resource.h"

// 加载静态库 winmm.lib
#pragma comment(lib, "winmm.lib")

void initSound() {
    // 初始化所有音乐资源
    mciSendString(("open " + getSound("bgm_main") + " alias main").c_str(), nullptr, 0, nullptr);
    mciSendString(("open " + getSound("bgm_game1") + " alias gaming1").c_str(), nullptr, 0, nullptr);
    mciSendString(("open " + getSound("bgm_game2") + " alias gaming2").c_str(), nullptr, 0, nullptr);
    mciSendString(("open " + getSound("hit") + " alias hit").c_str(), nullptr, 0, nullptr);
    // music是文件的相对路径
    // alias是将文件名music简称为bgm
}

void playSound(sound snd) {
    debug("play sound: ");
    switch (snd) {
        case MAIN:
            mciSendString("play main repeat", nullptr, 0, nullptr);
            break;
        case GAMING1:
            mciSendString("play gaming1 repeat", nullptr, 0, nullptr);
            break;
        case GAMING2:
            mciSendString("play gaming2 repeat", nullptr, 0, nullptr);
            break;
        case HIT:
            mciSendString("play hit", nullptr, 0, nullptr);
            break;
        default:
            error("no sound resources: " + std::to_string(snd));
            break;
    }
}

void closeSound(sound snd) {
    switch (snd) {
        case MAIN:
            mciSendString("close main", nullptr, 0, nullptr);
            break;
        case GAMING1:
            mciSendString("close gaming1", nullptr, 0, nullptr);
            break;
        case GAMING2:
            mciSendString("close gaming2", nullptr, 0, nullptr);
            break;
        case HIT:
            mciSendString("close hit", nullptr, 0, nullptr);
            break;
        default:
            error("no sound resources: " + std::to_string(snd));
            break;
    }
    initSound();
}

void closeSoundAll() {
    mciSendString("close main", nullptr, 0, nullptr);
    mciSendString("close gaming1", nullptr, 0, nullptr);
    mciSendString("close gaming2", nullptr, 0, nullptr);
    mciSendString("close hit", nullptr, 0, nullptr);
    initSound();
}

void setVolumn(int volumn) {
    mciSendString(("setaudio NOWMUSIC volume to " + std::to_string(volumn)).c_str(), nullptr, 0, nullptr);
}