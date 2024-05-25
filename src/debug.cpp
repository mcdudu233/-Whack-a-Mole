//
// Created by dudu233 on 2024/5/25.
//

#include "debug.h"

void debug(std::string msg) {
    if (DEBUG) {
        std::cout << "debug >>" << msg << std::endl;
    }
}

void info(std::string msg) {
    if (INFO) {
        std::cout << "info >>" << msg << std::endl;
    }
}

void error(std::string msg) {
    if (ERROR) {
        std::cout << "error >>" << msg << std::endl;
    }
}