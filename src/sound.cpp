//
// Created by dudu233 on 2024/6/8.
//

#include "sound.h"
#include "Mmsystem.h"
#include "debug.h"

sound::sound() {
    // ��ʼ������������Դ
    mciSendString("open bk_music.mp3 alias bgm", 0, 0, 0);
    // bk_music���ļ������·��
    // alias�ǽ��ļ���bk_music���Ϊbgm
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