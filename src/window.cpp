//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "graphics.h"
#include "resource.h"
#include <conio.h>
#include<iostream>

void drawButton(int x, int y, int width, int height, COLORREF color, const char *text, int textHeight, COLORREF textColor) {
    setfillcolor(color);
    solidroundrect(x, y, x + width, y + height, 20, 20);
    settextstyle(textHeight, 0, "黑体");
    setbkmode(TRANSPARENT);
    settextcolor(textColor);
    outtextxy(x + (width / 2) - textwidth(text) / 2, y + (height / 2) - textheight(text) / 2, text);
}

void init_graph(int width, int height) {
    debug("create " + std::to_string(width) + "x" + std::to_string(height) + " window, radio is " +
          std::to_string(1.0 * width / WINDOW_WIDTH) + "x" + std::to_string(1.0 * height / WINDOW_HEIGHT) + ".");
    // 创建绘图窗口 允许双击
    initgraph(width, height, EX_DBLCLKS);
    // 默认的分辨率为 800*600 如果不一样则缩放窗口
    setaspectratio(1.0 * width / WINDOW_WIDTH, 1.0 * height / WINDOW_HEIGHT);
    // 设置背景颜色 和 透明
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);

    //获取窗口句柄
    HWND h = GetHWnd();
    //修改窗口标题
    SetWindowText(h, "打地鼠小游戏");
}

void main_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        if (m.mkLButton || m.mkMButton || m.mkRButton) {
            if (x >= BUTTON_MAIN_STARTGAME_X && x <= BUTTON_MAIN_STARTGAME_XX && y >= BUTTON_MAIN_STARTGAME_Y && y <= BUTTON_MAIN_STARTGAME_YY) {
                debug("start button is clicked.");
                init_game_graph().join();
                break;
            } else if (x >= 20 && x <= 120 && y >= 530 && y <= 580) {
                debug("settings button is clicked.");
                init_settings_graph().join();
                break;
            } else if (x >= 640 && x <= 780 && y >= 530 && y <= 580) {
                debug("exit button is clicked.");
                exit(0);
            }
        }
    }
}

std::thread init_main_graph() {
    // 清空窗口
    cleardevice();
    // 加载主窗口图片
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // 绘制按钮
    drawButton(BUTTON_MAIN_STARTGAME_X, BUTTON_MAIN_STARTGAME_Y, BUTTON_MAIN_STARTGAME_WIDTH, BUTTON_MAIN_STARTGAME_HEIGHT, BUTTON_MAIN_COLOR, "开始游戏", 40, BUTTON_MAIN_TEXTCOLOR);
    drawButton(20, 530, 100, 50, BUTTON_MAIN_COLOR, "设置", 30, BUTTON_MAIN_TEXTCOLOR);
    drawButton(640, 530, 140, 50, BUTTON_MAIN_COLOR, "退出游戏", 30, BUTTON_MAIN_TEXTCOLOR);
    // 返回按钮点击监听线程
    return std::thread(main_listener);
}

void settings_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // TODO 监听设置的鼠标事件

    }
}

std::thread init_settings_graph() {
    // 清空窗口
    cleardevice();
    // 加载设置图片
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // TODO xb：做完以下内容以后删掉本行
    // 设置标题
    settextstyle(30, 0, _T("楷体"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("设置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 绘制难度选择标题
    settextstyle(30, 0, "楷体");
    setbkcolor(BLACK);
    outtextxy(100, 150, "游戏难度:");

    // 绘制难度按钮
    settextstyle(20, 10, "楷体");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "简单");

    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "中等");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "困难");




    // 音量设置
    // 返回按钮点击监听线程
    return std::thread(settings_listener);
}

void game_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // TODO 监听游戏中的鼠标事件
    }
}

std::thread init_game_graph() {
    // 清空窗口
    cleardevice();
    // 加载游戏图片
    IMAGE img;
    loadimage(&img, getPic("game"), 800, 600);
    putimage(0, 0, &img);
    // 返回按钮点击监听线程
    return std::thread(game_listener);
}