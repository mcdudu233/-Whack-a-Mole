#include "conio.h"
#include "debug.h"
#include "graphics.h"
#include "mole.h"
#include "window.h"

int main() {
    // 测试网页IDE
    debug("starting program.");
    srand((unsigned) time(NULL));// ��ʼ���������
    init_main_graph(800, 600);
    mole m1, m2;
    m1.show();
    m2.show();
    _getch();    // �����������
    closegraph();// �رջ�ͼ����
    return 0;
}
