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
// 难度选择函数
void nanduchoice () {
    int progressBarWidth = 400; // 进度条宽度
    int progressBarHeight = 20; // 进度条高度
    int x = 200;
    int y = 100;

    int difficulty = 0; // 难度初始值
    int maxDifficulty = 10; // 最大难度

    while (true) {
        // 绘制进度条背景
        setcolor(BLACK);
        rectangle(x, y, x + progressBarWidth, y + progressBarHeight);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(x + 1, y + 1, x + progressBarWidth - 1, y + progressBarHeight - 1);

        // 绘制当前进度
        setfillstyle(SOLID_FILL, BLUE);
        bar(x + 1, y + 1, x + 1 + (difficulty * (progressBarWidth - 2) / maxDifficulty), y + progressBarHeight - 1);

        // 显示难度文本
        setcolor(BLACK);
        settextstyle(30, 0, _T("楷体"));
        char text[20];
        sprintf(text, "难度: %d", difficulty);
        outtextxy(x, y - 30, text);

    }
}
void fenbianlvchoice() {
    int sliderWidth = 400; // 滑动条宽度
    int sliderHeight = 20; // 滑动条高度
    int x=200;
    int y=200;
    int minValue = 800 ; // 分辨率最小值
    int maxValue = 1920; // 分辨率最大值
    int resolution = minValue; // 当前分辨率

    while (true) {
        // 绘制滑动条背景
        setcolor(BLACK);
        rectangle(x, y, x + sliderWidth, y + sliderHeight);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(x + 1, y + 1, x + sliderWidth - 1, y + sliderHeight - 1);

        // 绘制滑块
        int sliderX = x + (resolution - minValue) * (sliderWidth - 10) / (maxValue - minValue);
        setfillstyle(SOLID_FILL, BLUE);
        bar(sliderX, y, sliderX + 10, y + sliderHeight);

        // 显示当前分辨率文本
        setcolor(BLACK);
        settextstyle(30, 0, _T("楷体"));
        char text[20];
        sprintf(text, "分辨率: %d", resolution);
        outtextxy(x, y - 30, text);
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
    settextcolor(WHITE);
    RECT r = {0, 0, 800, 50};
    drawtext(_T("设置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 游戏难度设置
    nanduchoice();
    // 分辨率设置
    fenbianlvchoice();



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