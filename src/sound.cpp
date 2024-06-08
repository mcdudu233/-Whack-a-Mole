//
// Created by dudu233 on 2024/6/8.
//

#include "sound.h"
#include "Mmsystem.h"
#include "debug.h"

sound::sound() {
    // 初始化所有音乐资源
    mciSendString("open bk_music.mp3 alias bgm", 0, 0, 0);
    // bk_music是文件的相对路径
    // alias是将文件名bk_music简称为bgm
}

void sound::playSound(sound_t snd) {
    switch (snd) {
        case MAIN:
            mciSendString("play bgm repeat", 0, 0, 0);
            break;
        default:
            error("no sound resources: " + std::to_string(snd));
            break;
    }
}

void sound::closeSound(sound_t snd) {
}

void sound::cloaeSoundAll() {
    mciSendString("close bgm", nullptr, 0, nullptr);
}