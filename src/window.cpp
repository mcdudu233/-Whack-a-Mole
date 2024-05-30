//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "graphics.h"

void init_main_graph(int width, int height) {
    debug("create " + std::to_string(width) + "x" + std::to_string(height) + " window, radio is " +
          std::to_string(1.0 * width / WINDOW_WIDTH) + "x" + std::to_string(1.0 * height / WINDOW_HEIGHT) + ".");
    // 创建绘图窗口 允许双击
    initgraph(width, height, EX_DBLCLKS);
    // 默认的分辨率为 800*600 如果不一样则缩放窗口
    setaspectratio(1.0 * width / WINDOW_WIDTH, 1.0 * height / WINDOW_HEIGHT);
    // 设置背景颜色 和 透明
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    // 清空窗口
    cleardevice();
    // 字体为黑体 黑色
    settextcolor(BLACK);
    settextstyle(40, 0, "黑体");
    outtextxy(100, 220, "开始游戏");
    outtextxy(20, 285, "设置");
}