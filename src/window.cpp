//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "game.h"
#include "graphics.h"
#include "resource.h"
#include "sound.h"

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// 根据缩放无阻塞的获取鼠标信息
MOUSEMSG mouseLast;
MOUSEMSG mouseMessage() {
    MOUSEMSG tmp;
    if (PeekMouseMsg(&tmp, true)) {
        mouseLast = tmp;
        // 根据缩放因子求值
        mouseLast.x = (short) ((float) mouseLast.x * WINDOW_WIDTH / (float) getwidth());
        mouseLast.y = (short) ((float) mouseLast.y * WINDOW_HEIGHT / (float) getheight());
    }
    return mouseLast;
}

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
        m = mouseMessage();
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

// 全局变量，记录当前的音量值
int volume = 50;// 初始音量值（0-100）
// 全局变量 ，用于设置中的刷新
IMAGE tmp_0;
IMAGE tmp_1;
IMAGE tmp_2;
// 全局变量，用于记录当前难度，默认难度为简单
Difficulty difficulty = EASY;

void settings_listener() {
    MOUSEMSG m;// 定义消息变量
    int x, y;
    while (true) {
        // 获取一条鼠标或按键消息
        m = mouseMessage();
        x = m.x;
        y = m.y;

        // 函数声明
        void drawOptionsList(int startX, int startY, int width, int height);
        void drawVolumeControl();
        void handleMouseDrag(int x, int y);
        switch (m.uMsg) {
            case WM_LBUTTONDOWN://  左键单击
            {
                if (x >= 50 && x <= 250 && y >= 200 && y <= 250) {
                    // 简单模式
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "楷体");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "简单");
                    difficulty = EASY;
                    break;
                } else if (x >= 50 && x <= 250 && y >= 300 && y <= 350) {
                    // 普通模式
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "楷体");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "普通");
                    difficulty = NORMAL;
                    break;
                } else if (x >= 50 && x <= 250 && y >= 400 && y <= 450) {
                    // 困难模式
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "楷体");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "困难");
                    difficulty = HARD;
                    break;
                } else if (x >= 340 && x <= 780 && y >= 530 && y <= 580) {
                    init_main_graph();// 返回主界面
                    break;
                } else if (x >= 310 && x <= 480 && y >= 150 && y <= 230) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "楷体");
                    init_graph(400, 300);
                    init_settings_graph();
                    break;
                } else if (x >= 310 && x <= 480 && y >= 230 && y <= 280) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "楷体");
                    init_graph(800, 600);
                    init_settings_graph();
                    break;
                } else if (x >= 500 && x <= 670 && y >= 150 && y <= 200) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "楷体");
                    init_graph(1200, 900);
                    init_settings_graph();
                    break;
                } else if (x >= 500 && x <= 670 && y >= 230 && y <= 280) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "楷体");
                    init_graph(1600, 1200);
                    init_settings_graph();
                    break;
                }
            }

            case (WM_LBUTTONDOWN && WM_MOUSEMOVE): {
                handleMouseDrag(x, y);
                drawVolumeControl();// 更新界面显示
                break;
            }
        }
    }
}


// 绘制音量调节界面
void drawVolumeControl() {
    // 绘制音量调节标题
    settextstyle(30, 0, "楷体");
    outtextxy(310, 320, "音量调节");

    // 绘制滑动条背景
    rectangle(350, 360, 750, 410);

    // 计算当前滑块的位置
    int sliderPos = 350 + volume * 400 / 100;

    // 绘制滑动条当前值
    setfillcolor(WHITE);
    solidrectangle(350, 360, sliderPos, 410);

    // 绘制滑块
    setfillcolor(WHITE);
    solidrectangle(sliderPos - 1, 360, sliderPos + 1, 410);

    // 显示当前音量值
    char volStr[20];
    sprintf(volStr, "音量: %d%%", volume);
    setVolumn(volume);
    outtextxy(310, 420, volStr);
}

// 处理鼠标拖动事件
void handleMouseDrag(int x, int y) {
    if (y >= 350 && y <= 420 && x >= 340 && x <= 760) {
        if (x < 350) x = 350;
        if (x > 750) x = 750;
        volume = (x - 350) * 100 / 400;
        putimage(350, 360, &tmp_0);
    }
}

void init_settings_graph() {
    // 清空窗口
    cleardevice();
    // 加载设置图片
    IMAGE img;
    loadimage(&img, getPic("game").c_str(), 800, 600);
    putimage(0, 0, &img);
    getimage(&tmp_0, 350, 360, 400, 150);
    getimage(&tmp_1, 160, 100, 100, 50);
    getimage(&tmp_2, 480, 100, 200, 50);
    // 包围框
    setcolor(WHITE);
    rectangle(10, 5, 790, 590);
    // 设置标题
    settextcolor(BLACK);
    settextstyle(30, 0, _T("楷体"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("设置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 设置返回按键
    drawButton(340, 530, 140, 50, BUTTON_MAIN_COLOR, "返回", 30, BUTTON_MAIN_TEXTCOLOR);
    // 绘制难度选择标题
    settextstyle(30, 0, "楷体");
    settextcolor(BLACK);
    outtextxy(25, 100, "游戏难度:");
    // 默认难度为简单
    switch (difficulty) {
        case EASY: {
            settextstyle(30, 0, "楷体");
            settextcolor(BLACK);
            outtextxy(160, 100, "简单");
            break;
        }
        case NORMAL: {
            settextstyle(30, 0, "楷体");
            settextcolor(BLACK);
            outtextxy(160, 100, "普通");
            break;
        }
        case HARD: {
            settextstyle(30, 0, "楷体");
            settextcolor(BLACK);
            outtextxy(160, 100, "困难");
            break;
        }
    }

    // 绘制难度按钮
    settextstyle(20, 10, "楷体");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "简单");
    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "普通");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "困难");

    // 分辨率设置
    // 绘制分辨率选择标题
    settextstyle(30, 0, "楷体");
    settextcolor(BLACK);
    outtextxy(310, 100, "分辨率选择:");
    settextstyle(30, 0, "楷体");
    // 读取当前分辨率
    int width = getwidth();  // 获取窗口宽度
    int height = getheight();// 获取窗口高度
    // 输出窗口大小
    char text[50];
    sprintf(text, "%d×", width);
    outtextxy(480, 100, text);// 在 (48, 100) 的位置输出宽度信息
    sprintf(text, "%d", height);
    outtextxy(560, 100, text);// 在 (560, 100) 的位置输出高度信息
    settextcolor(BLACK);


    // 绘制分辨率选择按钮
    settextstyle(30, 10, "楷体");
    rectangle(310, 150, 480, 200);
    outtextxy(350, 160, "400×300");
    //800*600选择模块
    rectangle(310, 230, 480, 280);
    outtextxy(350, 240, "800×600");
    //1280*720模块
    rectangle(500, 230, 670, 280);
    outtextxy(540, 240, "1600×1200");
    // 1920×1080模块
    rectangle(500, 150, 670, 200);
    outtextxy(540, 160, "1200×900");


    // 音量设置
    drawVolumeControl();

    // 返回按钮点击监听线程
    settings_listener();
}

void game_listener(game *game) {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = mouseMessage();
        x = m.x;
        y = m.y;

        // 监听游戏中的鼠标事件
        if (m.mkLButton) {
            if (x >= 340 && x <= 480 && y >= 530 && y <= 580) {
                // 销毁游戏
                game->destroy();
                init_main_graph();// 返回主界面
            }
        }
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
    // 绘制返回按键
    drawButton(340, 530, 140, 50, BUTTON_MAIN_COLOR, "返回", 30, BUTTON_MAIN_TEXTCOLOR);
    // 开始关卡
    game game(1, difficulty);
    // 返回按钮点击监听线程
    game_listener(&game);
}