//
// Created by dudu233 on 2024/5/26.
//

#include "window.h"
#include "debug.h"
#include "graphics.h"

void init_main_graph(int width, int height) {
    debug("create " + std::to_string(width) + "x" + std::to_string(height) + " window, radio is " +
          std::to_string(1.0 * width / WINDOW_WIDTH) + "x" + std::to_string(1.0 * height / WINDOW_HEIGHT) + ".");
    // ������ͼ���� ����˫��
    initgraph(width, height, EX_DBLCLKS);
    // Ĭ�ϵķֱ���Ϊ 800*600 �����һ�������Ŵ���
    setaspectratio(1.0 * width / WINDOW_WIDTH, 1.0 * height / WINDOW_HEIGHT);
    // ���ñ�����ɫ �� ͸��
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    // ��մ���
    cleardevice();
    // ����������ͼƬ
    IMAGE img;
    loadimage(&img, "../res/main.jpg", 800, 600);
    putimage(0, 0, &img);
    // ��䰴ť����
    setfillcolor(RGB(0xC3, 0x4A, 0x36));
    solidroundrect(280, 380, 500, 460, 20, 20);
    solidroundrect(20, 530, 120, 580, 20, 20);
    solidroundrect(640, 530, 780, 580, 20, 20);
    // ����Ϊ���� ��ɫ
    settextcolor(BLACK);
    settextstyle(40, 0, "����");
    outtextxy(310, 400, "��ʼ��Ϸ");
    settextstyle(30, 0, "����");
    outtextxy(42, 540, "����");
    outtextxy(650, 540, "�˳���Ϸ");
}

void init_main_listener() {
    bool flag = true;
    MOUSEMSG m;
    int x, y;
    while (flag) {
        m = GetMouseMsg();
        x = m.x;
        y = m.y;
        if (m.mkLButton || m.mkMButton || m.mkRButton) {
            if (x >= 280 && x <= 500 && y >= 380 && y <= 460) {
                debug("start button is clicked.");
                flag = false;
            } else if (x >= 20 && x <= 120 && y >= 530 && y <= 580) {
                debug("settings button is clicked.");
                flag = false;

            } else if (x >= 640 && x <= 780 && y >= 530 && y <= 580) {
                debug("exit button is clicked.");
                exit(0);
            }
        }
    }
}