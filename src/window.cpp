//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "conio.h"
#include "debug.h"
#include "game.h"
#include "graphics.h"
#include "resource.h"
#include "sound.h"
#include "vector"


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
                init_game_graph();
                break;
            } else if (x >= 20 && x <= 120 && y >= 530 && y <= 580) {
                debug("settings button is clicked.");
                init_settings_graph();
                break;
            } else if (x >= 640 && x <= 780 && y >= 530 && y <= 580) {
                debug("exit button is clicked.");
                exit(0);
            }
        }
    }
}

void init_main_graph() {
    // 清空窗口
    cleardevice();
    // 加载音效
    closeSoundAll();
    playSound(MAIN);
    // 加载主窗口图片
    IMAGE img;
    loadimage(&img, getPic("main").c_str(), 800, 600);
    putimage(0, 0, &img);
    // 绘制按钮
    drawButton(BUTTON_MAIN_STARTGAME_X, BUTTON_MAIN_STARTGAME_Y, BUTTON_MAIN_STARTGAME_WIDTH, BUTTON_MAIN_STARTGAME_HEIGHT, BUTTON_MAIN_COLOR, "开始游戏", 40, BUTTON_MAIN_TEXTCOLOR);
    drawButton(20, 530, 100, 50, BUTTON_MAIN_COLOR, "设置", 30, BUTTON_MAIN_TEXTCOLOR);
    drawButton(640, 530, 140, 50, BUTTON_MAIN_COLOR, "退出游戏", 30, BUTTON_MAIN_TEXTCOLOR);
    // 返回按钮点击监听线程
    main_listener();
}

void settings_listener() {
    ExMessage m;// 定义消息变量
    int x, y;
    while (true) {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        x = m.x;
        y = m.y;
        // TODO 监听设置的鼠标事件
        void drawResolutionDropdown();
        void handleMouseClick(int x, int y);
        void drawOptionsList(int startX, int startY, int width, int height);
        switch (m.message) {
            case WM_LBUTTONDOWN: {
                if (x >= 50 && x <= 250 && y >= 200 && y <= 250) {
                    // 简单模式
                }
                if (x >= 50 && x <= 250 && y >= 300 && y <= 350) {
                    // 普通模式
                }
                if (x >= 50 && x <= 250 && y >= 400 && y <= 450) {
                    // 困难模式
                }
            }

            case WM_RBUTTONDOWN: {
                handleMouseClick(m.x, m.y);
                drawResolutionDropdown();// 更新界面显示
            }
        }
    }
}
// 全局变量
int selectedResolutionIndex = 0;
std::vector<int> resolutions = {640, 800, 1024, 1280, 1920};// 分辨率列表
int volume = 50;                                            // 初始音量值（0-100）
// 绘制选项列表
void drawOptionsList(int startX, int startY, int width, int height) {
    setfillcolor(WHITE);
    setlinecolor(BLUE);
    solidrectangle(startX, startY, startX + width, startY + height);
    settextstyle(30, 0, "楷体");

    for (size_t i = 0; i < resolutions.size(); ++i) {
        char resStr[20];
        sprintf(resStr, "%d x %d", resolutions[i], resolutions[i]);
        outtextxy(startX + 10, startY + 10 + i * 30, resStr);
        if (i == selectedResolutionIndex) {
            setfillcolor(LIGHTGRAY);
            solidrectangle(startX + 5, startY + 5 + i * 30, startX + width - 5, startY + 30 + i * 30);
            setfillcolor(WHITE);
        }
    }
}
// 绘制分辨率选择界面
void drawResolutionDropdown() {
    // 绘制选择框
    setlinecolor(BLUE);
    rectangle(500, 80, 750, 150);
    settextstyle(30, 0, "楷体");
    outtextxy(310, 100, "分辨率选择");

    // 绘制当前选择的分辨率
    settextstyle(30, 0, "楷体");
    char resStr[20];
    sprintf(resStr, "%d x %d", resolutions[selectedResolutionIndex], resolutions[selectedResolutionIndex]);
    outtextxy(550, 100, resStr);
    // 如果列表被展开，绘制选项列表
    static bool isListVisible = false;
    if (isListVisible) {
        drawOptionsList(500, 80, 250, 70);
    }
}
// 处理鼠标点击事件
void handleMouseClick(int x, int y) {
    static bool isListVisible = false;
    if (x >= 500 && x <= 750 && y >= 80 && y <= 150) {
        isListVisible = !isListVisible;// 切换列表显示状态
        drawResolutionDropdown();
        return;
    }

    if (isListVisible) {
        for (size_t i = 0; i < resolutions.size(); ++i) {
            if (x >= 500 && x <= 750 && y >= 80 + i * 30 && y <= 130 + i * 30) {
                selectedResolutionIndex = i;
                isListVisible = false;// 点击后关闭列表
                drawResolutionDropdown();
                break;
            }
        }
    }
}

void init_settings_graph() {
    // 清空窗口
    cleardevice();
    // 加载设置图片
    IMAGE img;
    loadimage(&img, getPic("main").c_str(), 800, 600);
    putimage(0, 0, &img);
    // TODO xb：做完以下内容以后删掉本行
    // 设置标题
    settextstyle(30, 0, _T("楷体"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("设置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 绘制难度选择标题
    settextstyle(30, 0, "楷体");
    settextcolor(BLACK);
    outtextxy(75, 100, "游戏难度:");
    // 绘制难度按钮
    settextstyle(20, 10, "楷体");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "简单");

    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "中等");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "困难");

    // 分辨率设置
    drawResolutionDropdown();
    // 音量设置

    // 返回按钮点击监听线程
    settings_listener();
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

void init_game_graph() {
    // 清空窗口
    cleardevice();
    // 加载音效 随机选择一首
    closeSoundAll();
    if (rand() % 2 == 1) {
        playSound(GAMING1);
    } else {
        playSound(GAMING2);
    }
    // 加载游戏图片
    IMAGE img;
    loadimage(&img, getPic("game").c_str(), 800, 600);
    putimage(0, 0, &img);
    game g(20, HARD);
    // 返回按钮点击监听线程
    game_listener();
}