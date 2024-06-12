//
// Created by dudu233 on 2024/6/8.
//

#include "resource.h"

std::string getPic(std::string name) {
    std::string file = RES_PIC + name + RES_PIC_SUF;
    return file;
}

std::string getSound(std::string name) {
    std::string file = RES_SOUND + name + RES_SOUND_SUF;
    return file;
}