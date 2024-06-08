//
// Created by dudu233 on 2024/6/8.
//

#include "resource.h"
#include "debug.h"

std::string getPic(std::string name) {
    return RES_PIC + name + RES_PIC_SUF;
}

std::string getSound(std::string name) {
    return RES_SOUND + name + RES_SOUND_SUF;
}