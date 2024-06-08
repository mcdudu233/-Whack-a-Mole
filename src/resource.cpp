//
// Created by dudu233 on 2024/6/8.
//

#include "resource.h"

const char *getPic(std::string name) {
    std::string file = RES_PIC + name + RES_PIC_SUF;
    return file.c_str();
}

const char *getSound(std::string name) {
    std::string file = RES_SOUND + name + RES_SOUND_SUF;
    return file.c_str();
}