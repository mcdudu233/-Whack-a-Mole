//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "conio.h"
#include "debug.h"
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
    MOUSEMSG m;		// ������Ϣ����
    int x, y;
    while (true) {
        // ��ȡһ�����򰴼���Ϣ
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        // TODO �������õ�����¼�
        // ��������
        void drawOptionsList(int startX, int startY, int width, int height);
        void drawVolumeControl();
        void handleMouseDrag(int x,int y);
        switch(m.uMsg) {
            case WM_LBUTTONDOWN:   //  �������
            {
                if(x>=50&&x<=250&&y>=200&&y<=250) {
                    // ��ģʽ
                }
                else if(x>=50&&x<=250&&y>=300&&y<=350) {
                    // ��ͨģʽ
                }
                else if(x>=50&&x<=250&&y>=400&&y<=450) {
                    // ����ģʽ
                }else if (x >= 640 && x <= 780 && y >= 530 && y <= 580) {
                    init_main_graph(); // ����������
                }
            }

            case (WM_LBUTTONDOWN&&WM_MOUSEMOVE): {
                handleMouseDrag(m.x,m.y);
                drawVolumeControl(); // ���½�����ʾ

            }
        }
        }
    }

// ȫ�ֱ���
int selectedResolutionIndex = 0;
std::vector<std::pair<int, int>> resolutions = {{640, 480}, {800, 600}, {1024, 768}, {1280, 720}, {1920, 1080}}; // ���÷ֱ����б�
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

// �����������ڽ���
void drawVolumeControl() {

    // �����������ڱ���
    settextstyle(30, 0, "����");
    outtextxy(310, 230, "��������");

    // ���ƻ���������
    rectangle(350, 300, 750, 350);

    // ���㵱ǰ�����λ��
    int sliderPos = 350 + volume * 400 / 100;

    // ���ƻ�������ǰֵ
    setfillcolor(YELLOW);
    solidrectangle(350, 300, sliderPos, 350);

    // ���ƻ���
    setfillcolor(WHITE);
    solidrectangle(sliderPos - 5, 300, sliderPos + 5, 350);

    // ��ʾ��ǰ����ֵ
    char volStr[20];
    sprintf(volStr, "����: %d%%", volume);
    setVolumn(volume);
    outtextxy(310, 380, volStr);
}
// ��������϶��¼�
void handleMouseDrag(int x,int y) {
    if(y>=290&y<=360&x>=340&x<=760) {
        if (x < 350) x = 350;
        if (x > 750) x = 750;
        volume = (x - 350) * 100 / 400;
    }


}
// ���Ʒֱ���ѡ�����
void drawResolutionMenu() {
    // ���Ʊ���
    setbkcolor(WHITE);
    cleardevice();

    // ���Ʊ���
    settextstyle(20, 10, "����");
    outtextxy(300, 100, "ѡ��ֱ���");

    // ���Ʒֱ���ѡ��
    settextstyle(20, 10, "����");
    int y = 200;
    for (size_t i = 0; i < resolutions.size(); ++i) {
        char resStr[20];
        sprintf(resStr, "%d x %d", resolutions[i].first, resolutions[i].second);
        outtextxy(300, y, resStr);
        if (i == selectedResolutionIndex) {
            rectangle(295, y - 5, 505, y + 20);
        }
        y += 30;
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
    // ���÷��ذ���
    drawButton(640, 530, 140, 50, BUTTON_MAIN_COLOR, "����", 30, BUTTON_MAIN_TEXTCOLOR);
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
    // ���ذ�ť��������߳�
    game_listener();
}