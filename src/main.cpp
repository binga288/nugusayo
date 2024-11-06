#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    // 1. 顯示固定的 header
    std::cout << R"( _ __  _   _  __ _ _   _ ___  ___ _   _  ___
| '_ \| | | |/ _` | | | / __|/ _ \ | | |/ _ \
| | | | |_| | (_| | |_| \__ \  __/ |_| | (_) |
|_| |_|\__,_|\__, |\__,_|___/\___|\__, |\___/
             |___/                |___/)" << std::endl;

    // 2. 取得終端機的行列數，並檢查是否為 nullptr
    const char* colsEnv = std::getenv("COLUMNS");
    const char* rowsEnv = std::getenv("LINES");

    int termCols = (colsEnv) ? std::atoi(colsEnv) : 0;
    int termRows = (rowsEnv) ? std::atoi(rowsEnv) : 0;

    return 0;
}