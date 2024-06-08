//
// Created by dudu233 on 2024/6/8.
//

#ifndef WHACK_A_MOLE_SOUND_H
#define WHACK_A_MOLE_SOUND_H

typedef enum { MAIN,
               GAMING } sound_t;

class sound {
public:
    sound();
    void playSound(sound_t snd);
    void closeSound(sound_t snd);
    void cloaeSoundAll();
};


#endif//WHACK_A_MOLE_SOUND_H
