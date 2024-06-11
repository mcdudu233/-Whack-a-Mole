//
// Created by dudu233 on 2024/5/26.
//

#ifndef WHACK_A_MOLE_WINDOW_H
#define WHACK_A_MOLE_WINDOW_H

#include "thread"

// 默认分辨率大小 800*600
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUTTON_MAIN_TEXTCOLOR RGB(255, 255, 255)
#define BUTTON_MAIN_COLOR RGB(0xC3, 0x4A, 0x36)
#define BUTTON_MAIN_STARTGAME_WIDTH 220
#define BUTTON_MAIN_STARTGAME_HEIGHT 80
#define BUTTON_MAIN_STARTGAME_X 280
#define BUTTON_MAIN_STARTGAME_Y 380
#define BUTTON_MAIN_STARTGAME_XX (BUTTON_MAIN_STARTGAME_X + BUTTON_MAIN_STARTGAME_WIDTH)
#define BUTTON_MAIN_STARTGAME_YY (BUTTON_MAIN_STARTGAME_Y + BUTTON_MAIN_STARTGAME_HEIGHT)


void init_graph(int width, int height);
std::thread init_main_graph();
std::thread init_settings_graph();
std::thread init_game_graph();

#endif//WHACK_A_MOLE_WINDOW_H
