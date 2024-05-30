//
// Created by dudu233 on 2024/5/25.
//

#ifndef WHACK_A_MOLE_DEBUG_H
#define WHACK_A_MOLE_DEBUG_H

#include "iostream"

// 设置是否开启调试输
#define DEBUG true
#define INFO true
#define ERROR true

void debug(std::string msg);
void info(std::string msg);
void error(std::string msg);

#endif//WHACK_A_MOLE_DEBUG_H
