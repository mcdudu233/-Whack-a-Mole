//
// Created by dudu233 on 2024/6/8.
//

#include "sound.h"
#include "debug.h"
#include "graphics.h"
#include "mmsystem.h"

// ���ؾ�̬�� winmm.lib
#pragma comment(lib, "winmm.lib")

sound::sound() {
    // ��ʼ������������Դ
    mciSendString("open bk_music.mp3 alias bgm", nullptr, 0, nullptr);
    // bk_music���ļ������·��
    // alias�ǽ��ļ���bk_music���Ϊbgm
}

void sound::playSound(sound_t snd) {
    switch (snd) {
        case MAIN:
            mciSendString("play bgm repeat", nullptr, 0, nullptr);
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