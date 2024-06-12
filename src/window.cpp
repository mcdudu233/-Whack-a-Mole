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
// �Ѷ�ѡ����
void nanduchoice () {
    int progressBarWidth = 400; // ���������
    int progressBarHeight = 20; // �������߶�
    int x = 200;
    int y = 100;

    int difficulty = 0; // �Ѷȳ�ʼֵ
    int maxDifficulty = 10; // ����Ѷ�

    while (true) {
        // ���ƽ���������
        setcolor(BLACK);
        rectangle(x, y, x + progressBarWidth, y + progressBarHeight);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(x + 1, y + 1, x + progressBarWidth - 1, y + progressBarHeight - 1);

        // ���Ƶ�ǰ����
        setfillstyle(SOLID_FILL, BLUE);
        bar(x + 1, y + 1, x + 1 + (difficulty * (progressBarWidth - 2) / maxDifficulty), y + progressBarHeight - 1);

        // ��ʾ�Ѷ��ı�
        setcolor(BLACK);
        settextstyle(30, 0, _T("����"));
        char text[20];
        sprintf(text, "�Ѷ�: %d", difficulty);
        outtextxy(x, y - 30, text);

    }
}
void fenbianlvchoice() {
    int sliderWidth = 400; // ���������
    int sliderHeight = 20; // �������߶�
    int x=200;
    int y=200;
    int minValue = 800 ; // �ֱ�����Сֵ
    int maxValue = 1920; // �ֱ������ֵ
    int resolution = minValue; // ��ǰ�ֱ���

    while (true) {
        // ���ƻ���������
        setcolor(BLACK);
        rectangle(x, y, x + sliderWidth, y + sliderHeight);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(x + 1, y + 1, x + sliderWidth - 1, y + sliderHeight - 1);

        // ���ƻ���
        int sliderX = x + (resolution - minValue) * (sliderWidth - 10) / (maxValue - minValue);
        setfillstyle(SOLID_FILL, BLUE);
        bar(sliderX, y, sliderX + 10, y + sliderHeight);

        // ��ʾ��ǰ�ֱ����ı�
        setcolor(BLACK);
        settextstyle(30, 0, _T("����"));
        char text[20];
        sprintf(text, "�ֱ���: %d", resolution);
        outtextxy(x, y - 30, text);
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
    settextcolor(WHITE);
    RECT r = {0, 0, 800, 50};
    drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // ��Ϸ�Ѷ�����
    nanduchoice();
    // �ֱ�������
    fenbianlvchoice();



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