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

IMAGE tmp;
IMAGE tmp_1;
IMAGE tmp_2;
IMAGE tmp_3;
void settings_listener() {
    MOUSEMSG m;// ������Ϣ����
    int x, y;
    while (true) {
        // ��ȡһ�����򰴼���Ϣ
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // ��������
        void drawOptionsList(int startX, int startY, int width, int height);
        void drawVolumeControl();
        void handleMouseDrag(int x, int y);
        switch (m.uMsg) {
            case WM_LBUTTONDOWN://  �������
            {
                if (x >= 50 && x <= 250 && y >= 200 && y <= 250) {
                    // ��ģʽ
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "��");
                    break;
                } else if (x >= 50 && x <= 250 && y >= 300 && y <= 350) {
                    // ��ͨģʽ
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "��ͨ");
                    break;
                } else if (x >= 50 && x <= 250 && y >= 400 && y <= 450) {
                    // ����ģʽ
                    putimage(160, 100, &tmp_1);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(160, 100, "����");
                    break;
                } else if (x >= 340 && x <= 780 && y >= 530 && y <= 580) {
                    init_main_graph();// ����������
                    break;
                } else if (x >= 310 && x <= 480 && y >= 150 && y <= 230) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(480, 100, "800��600");
                    init_graph(800, 600);
                    init_settings_graph();
                    break;
                } else if (x >= 310 && x <= 480 && y >= 230 && y <= 280) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(480, 100, "1280��720");
                    init_graph(1280, 720);
                    init_settings_graph();
                    break;
                } else if (x >= 500 && x <= 670 && y >= 150 && y <= 200) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(480, 100, "1020��768");
                    init_graph(1020, 768);
                    init_settings_graph();
                    break;
                } else if (x >= 500 && x <= 670 && y >= 230 && y <= 280) {
                    putimage(480, 100, &tmp_2);
                    settextstyle(30, 0, "����");
                    settextcolor(BLACK);
                    outtextxy(1920, 1080, "1920��1080");
                    init_graph(1920, 1080);
                    init_settings_graph();
                    break;
                }
            }

            case (WM_LBUTTONDOWN && WM_MOUSEMOVE): {
                handleMouseDrag(m.x, m.y);
                drawVolumeControl();// ���½�����ʾ
                break;
            }
        }
    }
}

// ȫ�ֱ�������¼��ǰ������ֵ
int volume = 50;// ��ʼ����ֵ��0-100��

// �����������ڽ���
void drawVolumeControl() {
    // �����������ڱ���
    settextstyle(30, 0, "����");
    outtextxy(310, 320, "��������");

    // ���ƻ���������
    rectangle(350, 360, 750, 410);

    // ���㵱ǰ�����λ��
    int sliderPos = 350 + volume * 400 / 100;

    // ���ƻ�������ǰֵ
    setfillcolor(WHITE);
    solidrectangle(350, 360, sliderPos, 410);

    // ���ƻ���
    setfillcolor(WHITE);
    solidrectangle(sliderPos - 1, 360, sliderPos + 1, 410);

    // ��ʾ��ǰ����ֵ
    char volStr[20];
    sprintf(volStr, "����: %d%%", volume);
    setVolumn(volume);
    outtextxy(310, 420, volStr);
}

// ��������϶��¼�
void handleMouseDrag(int x, int y) {
    if (y >= 350 && y <= 420 && x >= 340 && x <= 760) {
        if (x < 350) x = 350;
        if (x > 750) x = 750;
        volume = (x - 350) * 100 / 400;
        putimage(350, 360, &tmp);
    }
}

void init_settings_graph() {
    // ��մ���
    cleardevice();
    // ��������ͼƬ
    IMAGE img;
    loadimage(&img, getPic("game").c_str(), 800, 600);
    putimage(0, 0, &img);
    getimage(&tmp, 350, 360, 400, 150);
    getimage(&tmp_1, 160, 100, 100, 50);
    getimage(&tmp_2, 480, 100, 200, 50);
    // ��Χ��
    setcolor(WHITE);
    rectangle(10, 5, 790, 590);
    // TODO xb���������������Ժ�ɾ������
    // ���ñ���
    settextcolor(BLACK);
    settextstyle(30, 0, _T("����"));
    RECT r = {0, 0, 800, 50};
    drawtext(_T("����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // ���÷��ذ���
    drawButton(340, 530, 140, 50, BUTTON_MAIN_COLOR, "����", 30, BUTTON_MAIN_TEXTCOLOR);
    // �����Ѷ�ѡ�����
    settextstyle(30, 0, "����");
    settextcolor(BLACK);
    outtextxy(25, 100, "��Ϸ�Ѷ�:");
    // Ĭ���Ѷ�Ϊ��
    settextstyle(30, 0, "����");
    settextcolor(BLACK);
    outtextxy(160, 100, "��");
    // �����ѶȰ�ť
    settextstyle(20, 10, "����");
    rectangle(50, 200, 250, 250);
    outtextxy(120, 215, "��");
    rectangle(50, 300, 250, 350);
    outtextxy(120, 315, "��ͨ");

    rectangle(50, 400, 250, 450);
    outtextxy(120, 415, "����");

    // �ֱ�������
    // ���Ʒֱ���ѡ�����
    settextstyle(30, 0, "����");
    settextcolor(BLACK);
    outtextxy(310, 100, "�ֱ���ѡ��:");
    settextstyle(30, 0, "����");
    // ��ȡ��ǰ�ֱ���
    int width = getwidth(); // ��ȡ���ڿ��
    int height = getheight(); // ��ȡ���ڸ߶�
    // ������ڴ�С
    char text[50];
    sprintf(text, "%d��", width);
    outtextxy(480, 100, text); // �� (48, 100) ��λ����������Ϣ
    sprintf(text, "%d", height);
    outtextxy(560, 100, text); // �� (560, 100) ��λ������߶���Ϣ
    settextcolor(BLACK);


    // ���Ʒֱ���ѡ��ť
    settextstyle(30, 10, "����");
    rectangle(310, 150, 480, 200);
    outtextxy(350, 160, "800��600");
    //800*600ѡ��ģ��
    rectangle(310, 230, 480, 280);
    outtextxy(350, 240, "1280��720");
    //1280*720ģ��
    rectangle(500, 230, 670, 280);
    outtextxy(540, 240, "1920��1080");
    // 1920��1080ģ��
    rectangle(500, 150, 670, 200);
    outtextxy(540, 160, "1020��768");


    // ��������
    drawVolumeControl();

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
        switch(m.uMsg) {
            case WM_LBUTTONDOWN: {  //  �������
                if (x >= 340 && x <= 780 && y >= 530 && y <= 580) {
                    init_main_graph();// ����������
                }

            }

        }
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
    game g(1, HARD);
    // ���ص�ǰ�ؿ����÷֣����ط���
    // ��ǰ�ؿ�
    settextcolor(BLACK);
    settextstyle(30, 0, _T("����"));
    outtextxy(10,10,"��ǰ�ؿ�:");
    // ���ط���
    settextcolor(BLACK);
    settextstyle(30, 0, _T("����"));
    outtextxy(10,50,"���ط���:");
    // ��ǰ�÷�
    settextcolor(BLACK);
    settextstyle(30, 0, _T("����"));
    outtextxy(10,90,"��ǰ����:");
    // ���Ʒ��ذ���
    drawButton(340, 530, 140, 50, BUTTON_MAIN_COLOR, "����", 30, BUTTON_MAIN_TEXTCOLOR);
    game game(20, HARD);
    // ���ذ�ť��������߳�
    game_listener();
}