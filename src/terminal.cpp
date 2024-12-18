// src/terminal.cpp
#include "terminal.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace Terminal {

std::optional<int> executeCommand(const std::string& command) {
    std::array<char, 128> buffer{};
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return std::nullopt;
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    int status = pclose(pipe);
    if (status != 0) {
        return std::nullopt;
    }
    try {
        return std::stoi(result);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<std::pair<int, int>> getTerminalSize() {
    const char* colsEnv = std::getenv("COLUMNS");
    const char* rowsEnv = std::getenv("LINES");

    int cols = 0;
    int rows = 0;

    try {
        if (colsEnv) {
            cols = std::stoi(colsEnv);
        }
        if (rowsEnv) {
            rows = std::stoi(rowsEnv);
        }
    } catch (...) {
        cols = 0;
        rows = 0;
    }

    if (cols == 0 || rows == 0) {
        auto colsOpt = executeCommand("tput cols");
        auto rowsOpt = executeCommand("tput lines");
        if (colsOpt && rowsOpt) {
            cols = *colsOpt;
            rows = *rowsOpt;
        }
    }

    if (cols > 0 && rows > 0) {
        return std::make_pair(cols, rows);
    } else {
        return std::nullopt;
    }
}

}  // namespace Terminal
