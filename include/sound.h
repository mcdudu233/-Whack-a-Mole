//
// Created by dudu233 on 2024/6/8.
//

#ifndef WHACK_A_MOLE_SOUND_H
#define WHACK_A_MOLE_SOUND_H

typedef enum { MAIN,
               GAMING1,
               GAMING2,
               HIT } sound;

void initSound();
void playSound(sound snd);
void closeSound(sound snd);
void closeSoundAll();
void setVolumn(int volumn);


#endif//WHACK_A_MOLE_SOUND_H
