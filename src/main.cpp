#include "conio.h"
#include "debug.h"
#include "graphics.h"
#include "sound.h"
#include "window.h"

int main() {
    debug("starting program.");
    srand((unsigned) time(NULL));// ��ʼ���������

    // ��ʼ����Ч��Դ
    initSound();
    // ��ʼ������
    init_graph(800, 600);
    init_main_graph();

    _getch();    // �����������
    closegraph();// �رջ�ͼ����
    return 0;
}
