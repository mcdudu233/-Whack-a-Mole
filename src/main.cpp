#include "conio.h"
#include "debug.h"
#include "graphics.h"

// 默认分辨率大小 800*600
#define WIDTH 800.0
#define HEIGHT 600.0

void init_main_graph(int width, int height) {
    debug("create " + std::to_string(width) + "x" + std::to_string(height) + " window, radio is " +
          std::to_string(width / WIDTH) + "x" + std::to_string(height / HEIGHT) + ".");
    // 创建绘图窗口
    initgraph(width, height);
    // 默认的分辨率为 800*600 如果不一样则缩放窗口
    setaspectratio(width / WIDTH, height / HEIGHT);
}

int main() {
    debug("starting program.");
    init_main_graph(800, 600);
    circle(200, 200, 100);// 画圆，圆心(200, 200)，半径 100
    _getch();             // 按任意键继续
    closegraph();         // 关闭绘图窗口
    return 0;
}
