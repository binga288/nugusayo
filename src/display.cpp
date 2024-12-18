// src/display.cpp
#include "display.h"

#include <iostream>

namespace Display {

const char* HEADER_TEXT = R"( _ __  _   _  __ _ _   _ ___  ___ _   _  ___
| '_ \| | | |/ _` | | | / __|/ _ \ | | |/ _ \
| | | | |_| | (_| | |_| \__ \  __/ |_| | (_) |
|_| |_|\__,_|\__, |\__,_|___/\___|\__, |\___/
             |___/                |___/)";

void displayHeader() { std::cout << HEADER_TEXT << std::endl; }

}  // namespace Display
