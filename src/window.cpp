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
    // ��մ���
    cleardevice();
    // ����������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // ���ư�ť
    drawButton(BUTTON_MAIN_STARTGAME_X, BUTTON_MAIN_STARTGAME_Y, BUTTON_MAIN_STARTGAME_WIDTH, BUTTON_MAIN_STARTGAME_HEIGHT, BUTTON_MAIN_COLOR, "��ʼ��Ϸ", 40, BUTTON_MAIN_TEXTCOLOR);
    drawButton(20, 530, 100, 50, BUTTON_MAIN_COLOR, "����", 30, BUTTON_MAIN_TEXTCOLOR);
    drawButton(640, 530, 140, 50, BUTTON_MAIN_COLOR, "�˳���Ϸ", 30, BUTTON_MAIN_TEXTCOLOR);
    // ���ذ�ť��������߳�
    return std::thread(main_listener);
}

void settings_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // TODO �������õ�����¼�

    }
}

std::thread init_settings_graph() {
    // ��մ���
    cleardevice();
    // ��������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main"), 800, 600);
    putimage(0, 0, &img);
    // TODO xb���������������Ժ�ɾ������
    // ���ñ���
    settextstyle(30, 0, _T("����"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // �����Ѷ�ѡ�����
    settextstyle(30, 0, "����");
    setbkcolor(BLACK);
    outtextxy(100, 150, "��Ϸ�Ѷ�:");

    // �����ѶȰ�ť
    settextstyle(20, 10, "����");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "��");

    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "�е�");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "����");




    // ��������
    // ���ذ�ť��������߳�
    return std::thread(settings_listener);
}

void game_listener() {
    MOUSEMSG m;
    int x, y;
    while (true) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // TODO ������Ϸ�е�����¼�
    }
}

std::thread init_game_graph() {
    // ��մ���
    cleardevice();
    // ������ϷͼƬ
    IMAGE img;
    loadimage(&img, getPic("game"), 800, 600);
    putimage(0, 0, &img);
    // ���ذ�ť��������߳�
    return std::thread(game_listener);
}