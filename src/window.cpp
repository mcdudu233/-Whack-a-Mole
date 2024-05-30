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
    // ����Ϊ���� ��ɫ
    settextcolor(BLACK);
    settextstyle(40, 0, "����");
    outtextxy(100, 220, "��ʼ��Ϸ");
    outtextxy(20, 285, "����");
}