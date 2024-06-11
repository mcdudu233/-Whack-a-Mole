//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "graphics.h"
#include "resource.h"
#include <conio.h>

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
    // 游戏难度设置
    // 定义难度等级
    enum Difficulty {
        EASY,
        NORMAL,
        HARD
    };

    // 难度选择结构体
    struct DifficultySelection {
        int x, y;         // 难度选择位置
        int width, height; // 难度选择尺寸
        Difficulty currentDifficulty; // 当前选择的难度
    };
    settextstyle(16, 0, _T("黑体"));
    settextcolor(BLACK);
    // 难度选择初始化
    DifficultySelection selection = { 100, 200, 200, 50, EASY };
    setfillcolor(RGB(200, 200, 200));
    fillrectangle(selection.x, selection.y, selection.x + selection.width, selection.y + selection.height);

    // 绘制难度选项
    settextcolor(BLACK);
    TCHAR difficultyStrings[3][10] = {_T("简单"), _T("普通"), _T("困难")};
    for (int i = 0; i < 3; i++) {
        outtextxy(selection.x + 20, selection.y + 20 + i * 30, difficultyStrings[i]);
    }

    // 根据当前难度，绘制选择标记
    switch (selection.currentDifficulty) {
        case EASY:
            outtextxy(selection.x + 20, selection.y + 20, _T("->"));
        break;
        case NORMAL:
            outtextxy(selection.x + 20, selection.y + 50, _T("->"));
        break;
        case HARD:
            outtextxy(selection.x + 20, selection.y + 80, _T("->"));
        break;
    }
    // 处理难度选择
    while (true) {
        // 检测鼠标点击
        ExMessage msg;
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    // 根据鼠标点击位置切换难度
                        int difficulty = (msg.x - selection.x) / 60; // 假设每个难度选项宽度为60像素
                selection.currentDifficulty = (Difficulty)difficulty;
                // 重新绘制难度选择
                setfillcolor(RGB(200, 200, 200));
                fillrectangle(selection.x, selection.y, selection.x + selection.width, selection.y + selection.height);

                // 绘制难度选项
                settextcolor(BLACK);
                TCHAR difficultyStrings[3][10] = {_T("简单"), _T("普通"), _T("困难")};
                for (int i = 0; i < 3; i++) {
                    outtextxy(selection.x + 20, selection.y + 20 + i * 30, difficultyStrings[i]);
                }

                // 根据当前难度，绘制选择标记
                switch (selection.currentDifficulty) {
                    case EASY:
                        outtextxy(selection.x + 20, selection.y + 20, _T("->"));
                    break;
                    case NORMAL:
                        outtextxy(selection.x + 20, selection.y + 50, _T("->"));
                    break;
                    case HARD:
                        outtextxy(selection.x + 20, selection.y + 80, _T("->"));
                    break;
                }
                break;
                    // 右键点击退出难度选择

            }
        }
        
    }

    // 分辨率设置
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