//
// Created by dudu233 on 2024/6/8.
//

#ifndef WHACK_A_MOLE_RESOURCE_H
#define WHACK_A_MOLE_RESOURCE_H

#include "string"

// 图片文件夹和后缀
#define RES_PIC "../res/pics/"
#define RES_PIC_JPG ".jpg"
#define RES_PIC_PNG ".png"
// 音频文件夹和后缀
#define RES_SOUND "../res/sounds/"
#define RES_SOUND_SUF ".mp3"

std::string getPic(std::string name);
std::string getPicJPG(std::string name);
std::string getPicPNG(std::string name);
std::string getSound(std::string name);

#endif//WHACK_A_MOLE_RESOURCE_H
