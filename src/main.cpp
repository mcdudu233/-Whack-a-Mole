#include "conio.h"
#include "debug.h"
#include "graphics.h"
#include "sound.h"
#include "window.h"

int main() {
    debug("starting program.");
    srand((unsigned) time(NULL));// 初始化随机种子

    // 初始化音效资源
    initSound();
    // 初始化界面
    init_graph(800, 600);
    init_main_graph();

    _getch();    // 按任意键继续
    closegraph();// 关闭绘图窗口
    return 0;
}
