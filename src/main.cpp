#include "conio.h"
#include "debug.h"
#include "game.h"
#include "graphics.h"
#include "window.h"

int main() {
    debug("starting program.");
    srand((unsigned) time(NULL));// ��ʼ���������

    // ��ʼ������
    init_graph(800, 600);
    init_main_graph().join();

    _getch();    // �����������
    closegraph();// �رջ�ͼ����
    return 0;
}
