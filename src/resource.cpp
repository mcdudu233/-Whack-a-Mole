//
// Created by dudu233 on 2024/6/8.
//

#include "resource.h"

// 所有图片资源
IMAGE IMG_HOLE;
IMAGE IMG_HAMMER;
IMAGE IMG_HAMMER_DOWN;
IMAGE IMG_MOLE1;
IMAGE IMG_MOLE2;
IMAGE IMG_MOLE3;
IMAGE IMG_MOLE4;
IMAGE IMG_MOLE5;

void initResource() {
    // 加载所需图片
    loadimage(&IMG_HOLE, getPicPNG("hole").c_str(), 100, 50);
    loadimage(&IMG_HAMMER, getPicPNG("hammer").c_str(), 100, 100);
    loadimage(&IMG_HAMMER_DOWN, getPicPNG("hammer_down").c_str(), 100, 100);
    loadimage(&IMG_MOLE1, getPicPNG("mole1").c_str(), 40, 20);
    loadimage(&IMG_MOLE2, getPicPNG("mole2").c_str(), 40, 25);
    loadimage(&IMG_MOLE3, getPicPNG("mole3").c_str(), 40, 30);
    loadimage(&IMG_MOLE4, getPicPNG("mole4").c_str(), 40, 35);
    loadimage(&IMG_MOLE5, getPicPNG("mole5").c_str(), 40, 30);
}

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

// 支持透明PNG的图片放置
void putImage(int x, int y, IMAGE img) {
    IMAGE img1;
    DWORD *d1;
    img1 = img;
    d1 = GetImageBuffer(&img1);
    float h, s, l;
    for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
        RGBtoHSL(BGR(d1[i]), &h, &s, &l);
        if (l < 0.03) {
            d1[i] = BGR(WHITE);
        }
        if (d1[i] != BGR(WHITE)) {
            d1[i] = 0;
        }
    }
    putimage(x, y, &img1, SRCAND);
    putimage(x, y, &img, SRCPAINT);
}