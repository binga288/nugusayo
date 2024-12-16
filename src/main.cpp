#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // 檢查是否有傳入 --colorful 參數
    bool colorful = false;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--colorful") {
            colorful = true;
            break;
        }
    }

    // 1. 顯示固定的 header
    std::cout << R"( _ __  _   _  __ _ _   _ ___  ___ _   _  ___
| '_ \| | | |/ _` | | | / __|/ _ \ | | |/ _ \
| | | | |_| | (_| | |_| \__ \  __/ |_| | (_) |
|_| |_|\__,_|\__, |\__,_|___/\___|\__, |\___/
             |___/                |___/)"
              << std::endl;

    // 2. 取得終端機的行列數，並檢查是否為 nullptr
    const char* colsEnv = std::getenv("COLUMNS");
    const char* rowsEnv = std::getenv("LINES");

    int termCols = (colsEnv) ? std::atoi(colsEnv) : 0;
    int termRows = (rowsEnv) ? std::atoi(rowsEnv) : 0;

    // 如果無法讀取環境變數，則使用 `tput` 指令
    if (termCols == 0 || termRows == 0) {
        FILE* pipe = popen("tput cols", "r");
        if (pipe) {
            fscanf(pipe, "%d", &termCols);
            pclose(pipe);
        }
        pipe = popen("tput lines", "r");
        if (pipe) {
            fscanf(pipe, "%d", &termRows);
            pclose(pipe);
        }
    }

    if (termCols == 0 || termRows == 0) {
        std::cerr << "無法取得終端機解析度" << std::endl;
        return 1;
    }

    // 3. 計算去掉 header 後的有效行數
    int jp2aHeight = termRows - 7;

    // 4. 使用 jp2a 指令來顯示圖片
    std::string jp2aCommand = "jp2a --width=" + std::to_string(termCols) +
                              " --height=" + std::to_string(jp2aHeight);

    // 如果有傳入 --colorful，則加入 --color (或 --colors，看 jp2a 的實際參數)
    if (colorful) {
        jp2aCommand += " --color";
    }

    jp2aCommand += " images.png";

    system(jp2aCommand.c_str());

    return 0;
}
