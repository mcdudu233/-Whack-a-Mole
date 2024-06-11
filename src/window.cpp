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
    // ��Ϸ�Ѷ�����
    // �����Ѷȵȼ�
    enum Difficulty {
        EASY,
        NORMAL,
        HARD
    };

    // �Ѷ�ѡ��ṹ��
    struct DifficultySelection {
        int x, y;         // �Ѷ�ѡ��λ��
        int width, height; // �Ѷ�ѡ��ߴ�
        Difficulty currentDifficulty; // ��ǰѡ����Ѷ�
    };
    settextstyle(16, 0, _T("����"));
    settextcolor(BLACK);
    // �Ѷ�ѡ���ʼ��
    DifficultySelection selection = { 100, 200, 200, 50, EASY };
    setfillcolor(RGB(200, 200, 200));
    fillrectangle(selection.x, selection.y, selection.x + selection.width, selection.y + selection.height);

    // �����Ѷ�ѡ��
    settextcolor(BLACK);
    TCHAR difficultyStrings[3][10] = {_T("��"), _T("��ͨ"), _T("����")};
    for (int i = 0; i < 3; i++) {
        outtextxy(selection.x + 20, selection.y + 20 + i * 30, difficultyStrings[i]);
    }

    // ���ݵ�ǰ�Ѷȣ�����ѡ����
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
    // �����Ѷ�ѡ��
    while (true) {
        // ��������
        ExMessage msg;
        if (peekmessage(&msg, EM_MOUSE)) {
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    // ���������λ���л��Ѷ�
                        int difficulty = (msg.x - selection.x) / 60; // ����ÿ���Ѷ�ѡ����Ϊ60����
                selection.currentDifficulty = (Difficulty)difficulty;
                // ���»����Ѷ�ѡ��
                setfillcolor(RGB(200, 200, 200));
                fillrectangle(selection.x, selection.y, selection.x + selection.width, selection.y + selection.height);

                // �����Ѷ�ѡ��
                settextcolor(BLACK);
                TCHAR difficultyStrings[3][10] = {_T("��"), _T("��ͨ"), _T("����")};
                for (int i = 0; i < 3; i++) {
                    outtextxy(selection.x + 20, selection.y + 20 + i * 30, difficultyStrings[i]);
                }

                // ���ݵ�ǰ�Ѷȣ�����ѡ����
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
                    // �Ҽ�����˳��Ѷ�ѡ��

            }
        }
        
    }

    // �ֱ�������
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