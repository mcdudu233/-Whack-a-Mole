//
// Created by dudu233 on 2024/6/8.
//

#include "resource.h"

std::string getPic(std::string name) {
    return getPicJPG(name);
}

std::string getPicJPG(std::string name) {
    std::string file = RES_PIC + name + RES_PIC_JPG;
    return file;
}

std::string getPicPNG(std::string name) {
    std::string file = RES_PIC + name + RES_PIC_PNG;
    return file;
}

std::string getSound(std::string name) {
    std::string file = RES_SOUND + name + RES_SOUND_SUF;
    return file;
}