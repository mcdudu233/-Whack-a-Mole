//
// Created by dudu233 on 2024/6/8.
//

#ifndef WHACK_A_MOLE_RESOURCE_H
#define WHACK_A_MOLE_RESOURCE_H

#include "string"

// ͼƬ�ļ��кͺ�׺
#define RES_PIC "../res/pics/"
#define RES_PIC_SUF ".jpg"
// ��Ƶ�ļ��кͺ�׺
#define RES_SOUND "../res/sounds/"
#define RES_SOUND_SUF ".mp3"

std::string getPic(std::string name);
std::string getSound(std::string name);

#endif//WHACK_A_MOLE_RESOURCE_H
