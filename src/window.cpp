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
    // ��մ���
    cleardevice();
    // ������Ч
    closeSoundAll();
    playSound(MAIN);
    // ����������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main").c_str(), 800, 600);
    putimage(0, 0, &img);
    // ���ư�ť
    drawButton(BUTTON_MAIN_STARTGAME_X, BUTTON_MAIN_STARTGAME_Y, BUTTON_MAIN_STARTGAME_WIDTH, BUTTON_MAIN_STARTGAME_HEIGHT, BUTTON_MAIN_COLOR, "��ʼ��Ϸ", 40, BUTTON_MAIN_TEXTCOLOR);
    drawButton(20, 530, 100, 50, BUTTON_MAIN_COLOR, "����", 30, BUTTON_MAIN_TEXTCOLOR);
    drawButton(640, 530, 140, 50, BUTTON_MAIN_COLOR, "�˳���Ϸ", 30, BUTTON_MAIN_TEXTCOLOR);
    // ���ذ�ť��������߳�
    main_listener();
}

void settings_listener() {
    ExMessage m;// ������Ϣ����
    int x, y;
    while (true) {
        // ��ȡһ�����򰴼���Ϣ
        m = getmessage(EX_MOUSE | EX_KEY);
        x = m.x;
        y = m.y;
        // TODO �������õ�����¼�
        void drawResolutionDropdown();
        void handleMouseClick(int x, int y);
        void drawOptionsList(int startX, int startY, int width, int height);
        switch (m.message) {
            case WM_LBUTTONDOWN: {
                if (x >= 50 && x <= 250 && y >= 200 && y <= 250) {
                    // ��ģʽ
                }
                if (x >= 50 && x <= 250 && y >= 300 && y <= 350) {
                    // ��ͨģʽ
                }
                if (x >= 50 && x <= 250 && y >= 400 && y <= 450) {
                    // ����ģʽ
                }
            }

            case WM_RBUTTONDOWN: {
                handleMouseClick(m.x, m.y);
                drawResolutionDropdown();// ���½�����ʾ
            }
        }
    }
}
// ȫ�ֱ���
int selectedResolutionIndex = 0;
std::vector<int> resolutions = {640, 800, 1024, 1280, 1920};// �ֱ����б�
int volume = 50;                                            // ��ʼ����ֵ��0-100��
// ����ѡ���б�
void drawOptionsList(int startX, int startY, int width, int height) {
    setfillcolor(WHITE);
    setlinecolor(BLUE);
    solidrectangle(startX, startY, startX + width, startY + height);
    settextstyle(30, 0, "����");

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
// ���Ʒֱ���ѡ�����
void drawResolutionDropdown() {
    // ����ѡ���
    setlinecolor(BLUE);
    rectangle(500, 80, 750, 150);
    settextstyle(30, 0, "����");
    outtextxy(310, 100, "�ֱ���ѡ��");

    // ���Ƶ�ǰѡ��ķֱ���
    settextstyle(30, 0, "����");
    char resStr[20];
    sprintf(resStr, "%d x %d", resolutions[selectedResolutionIndex], resolutions[selectedResolutionIndex]);
    outtextxy(550, 100, resStr);
    // ����б�չ��������ѡ���б�
    static bool isListVisible = false;
    if (isListVisible) {
        drawOptionsList(500, 80, 250, 70);
    }
}
// ����������¼�
void handleMouseClick(int x, int y) {
    static bool isListVisible = false;
    if (x >= 500 && x <= 750 && y >= 80 && y <= 150) {
        isListVisible = !isListVisible;// �л��б���ʾ״̬
        drawResolutionDropdown();
        return;
    }

    if (isListVisible) {
        for (size_t i = 0; i < resolutions.size(); ++i) {
            if (x >= 500 && x <= 750 && y >= 80 + i * 30 && y <= 130 + i * 30) {
                selectedResolutionIndex = i;
                isListVisible = false;// �����ر��б�
                drawResolutionDropdown();
                break;
            }
        }
    }
}

void init_settings_graph() {
    // ��մ���
    cleardevice();
    // ��������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("main").c_str(), 800, 600);
    putimage(0, 0, &img);
    // TODO xb���������������Ժ�ɾ������
    // ���ñ���
    settextstyle(30, 0, _T("����"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // �����Ѷ�ѡ�����
    settextstyle(30, 0, "����");
    settextcolor(BLACK);
    outtextxy(75, 100, "��Ϸ�Ѷ�:");
    // �����ѶȰ�ť
    settextstyle(20, 10, "����");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "��");

    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "�е�");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "����");

    // �ֱ�������
    drawResolutionDropdown();
    // ��������

    // ���ذ�ť��������߳�
    settings_listener();
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

void init_game_graph() {
    // ��մ���
    cleardevice();
    // ������Ч ���ѡ��һ��
    closeSoundAll();
    if (rand() % 2 == 1) {
        playSound(GAMING1);
    } else {
        playSound(GAMING2);
    }
    // ������ϷͼƬ
    IMAGE img;
    loadimage(&img, getPic("game").c_str(), 800, 600);
    putimage(0, 0, &img);
    game g(20, HARD);
    // ���ذ�ť��������߳�
    game_listener();
}