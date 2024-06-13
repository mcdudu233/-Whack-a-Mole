//
// Created by dudu233 on 2024/6/8.
//

#ifndef WHACK_A_MOLE_RESOURCE_H
#define WHACK_A_MOLE_RESOURCE_H

#include "easyx.h"
#include "string"

// ͼƬ�ļ��кͺ�׺
#define RES_PIC "../res/pics/"
#define RES_PIC_JPG ".jpg"
#define RES_PIC_PNG ".png"
// ��Ƶ�ļ��кͺ�׺
#define RES_SOUND "../res/sounds/"
#define RES_SOUND_SUF ".mp3"

// ����ͼƬ��Դ
extern IMAGE IMG_HOLE;
extern IMAGE IMG_HAMMER;
extern IMAGE IMG_HAMMER_DOWN;
extern IMAGE IMG_MOLE1;

void initResource();
std::string getPic(std::string name);
std::string getPicJPG(std::string name);
std::string getPicPNG(std::string name);
std::string getSound(std::string name);
void putImage(int x, int y, IMAGE img);

#endif//WHACK_A_MOLE_RESOURCE_H
