//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "graphics.h"
#include "resource.h"

void drawButton(int x, int y, int width, int height, COLORREF color, const char *text, int textHeight, COLORREF textColor) {
    setfillcolor(color);
    solidroundrect(x, y, x + width, y + height, 20, 20);
    settextstyle(textHeight, 0, "����");
    setbkmode(TRANSPARENT);
    settextcolor(textColor);
    outtextxy(x + (width / 2) - textwidth(text) / 2, y + (height / 2) - textheight(text) / 2, text);
}

void init_graph(int width, int height) {
    debug("create " + std::to_string(width) + "x" + std::to_string(height) + " window, radio is " +
          std::to_string(1.0 * width / WINDOW_WIDTH) + "x" + std::to_string(1.0 * height / WINDOW_HEIGHT) + ".");
    // ������ͼ���� ����˫��
    initgraph(width, height, EX_DBLCLKS);
    // Ĭ�ϵķֱ���Ϊ 800*600 �����һ�������Ŵ���
    setaspectratio(1.0 * width / WINDOW_WIDTH, 1.0 * height / WINDOW_HEIGHT);
    // ���ñ�����ɫ �� ͸��
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);

    //��ȡ���ھ��
    HWND h = GetHWnd();
    //�޸Ĵ��ڱ���
    SetWindowText(h, "�����С��Ϸ");
}

void main_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        if (m.mkLButton || m.mkMButton || m.mkRButton) {
            if (x >= 280 && x <= 500 && y >= 380 && y <= 460) {
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
    // ��մ���
    cleardevice();
    // ����������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // ���ư�ť
    drawButton(280, 380, 220, 80, RGB(0xC3, 0x4A, 0x36), "��ʼ��Ϸ", 40, RGB(255, 255, 255));
    drawButton(20, 530, 100, 50, RGB(0xC3, 0x4A, 0x36), "����", 30, RGB(255, 255, 255));
    drawButton(640, 530, 140, 50, RGB(0xC3, 0x4A, 0x36), "�˳���Ϸ", 30, RGB(255, 255, 255));
    // ���ذ�ť��������߳�
    return std::thread(main_listener);
}

void settings_listener() {
    // ��մ���
    cleardevice();
    // ����������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // �ֱ�������
    // ��������
}

std::thread init_settings_graph() {
    // ���ذ�ť��������߳�
    return std::thread(settings_listener);
}

void game_listener() {
}

std::thread init_game_graph() {
    // ���ذ�ť��������߳�
    return std::thread(game_listener);
}