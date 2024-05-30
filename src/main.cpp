#include "conio.h"
#include "debug.h"
#include "graphics.h"
#include "mole.h"
#include "window.h"

int main() {
    // 测试网页IDE
    debug("starting program.");
    srand((unsigned) time(NULL));// 初始化随机种子
    init_main_graph(800, 600);
    mole m1, m2;
    m1.show();
    m2.show();
    _getch();    // 按任意键继续
    closegraph();// 关闭绘图窗口
    return 0;
}
