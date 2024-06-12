#include "conio.h"
#include "debug.h"
#include "game.h"
#include "graphics.h"
#include "window.h"

int main() {
    debug("starting program.");
    srand((unsigned) time(NULL));// 初始化随机种子

    // 初始化界面
    init_graph(800, 600);
    init_main_graph().join();

    _getch();    // 按任意键继续
    closegraph();// 关闭绘图窗口
    return 0;
}
