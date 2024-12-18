// main.cpp
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <random>

#include "args.h"
#include "display.h"
#include "jp2a.h"
#include "terminal.h"

// Constants
constexpr int HEADER_HEIGHT = 7;
constexpr const char* DEFAULT_IMAGE_FILE =
    "images/image1.png";                          // 更新預設圖片路徑
constexpr const char* IMAGES_FOLDER = "images/";  // 圖片資料夾路徑
constexpr int NUM_IMAGES = 15;                    // 圖片數量

// Function to print help message
void printHelp() {
    std::cout << "Usage: nuguseyo [OPTIONS]\n"
        << "Options:\n"
              << "  --path <image_path>     指定要加載的圖片路徑 (預設: "
                 "images/image1.png)\n"
              << "  --random                隨機選擇 images 資料夾中的一張圖片 "
                 "(image1.png ~ image15.png)\n"
              << "  --output <file_path>    將 ASCII 藝術圖輸出到指定的文件\n"
        << "  --colorful              啟用彩色輸出\n"
        << "  --help                  顯示此幫助信息\n";
}

int main(int argc, char* argv[]) {
    // 如果使用了 --help，顯示幫助信息並退出
    if (Args::isFlagEnabled(argc, argv, "--help")) {
        printHelp();
        return EXIT_SUCCESS;
    }

    // Parse command-line arguments
    bool colorful = Args::isFlagEnabled(argc, argv, "--colorful");
    bool random = Args::isFlagEnabled(argc, argv, "--random");
    std::string outputPath =
        Args::getArgumentValue(argc, argv, "--output");  // 新增解析 --output

    // 獲取 --path 參數的值，若未提供則使用預設路徑或隨機選擇
    std::string imagePath = Args::getArgumentValue(argc, argv, "--path");

    if (random) {
        // 使用 --random 參數，隨機選擇一張圖片
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, NUM_IMAGES);
        int randomImage = dis(gen);
        imagePath = std::string(IMAGES_FOLDER) + "image" +
                    std::to_string(randomImage) + ".png";
        std::cout << "隨機選擇的圖片: " << imagePath << std::endl;
    } else if (imagePath.empty()) {
        // 未使用 --random 且未指定 --path，使用預設圖片
        imagePath = DEFAULT_IMAGE_FILE;  // 預設圖片路徑
    }

    // 檢查圖片文件是否存在
    if (!std::filesystem::exists(imagePath)) {
        std::cerr << "Error: image file \"" << imagePath << "\" not exists."
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Display header
    Display::displayHeader();

    // Get terminal size
    auto terminalSizeOpt = Terminal::getTerminalSize();
    if (!terminalSizeOpt) {
        std::cerr << "Unable to determine terminal size." << std::endl;
        return EXIT_FAILURE;
    }

    int termCols = terminalSizeOpt->first;
    int termRows = terminalSizeOpt->second;

    // Calculate the height for jp2a
    int jp2aHeight = termRows - HEADER_HEIGHT;
    if (jp2aHeight <= 0) {
        std::cerr << "Terminal size too small to display image." << std::endl;
        return EXIT_FAILURE;
    }

    // Build the jp2a command
    std::string jp2aCommand =
        Jp2a::buildJp2aCommand(termCols, jp2aHeight, colorful, imagePath);

    if (!outputPath.empty()) {
        // 如果指定了 --output，將 jp2a 的輸出重定向到指定文件
        jp2aCommand += " > " + outputPath;
        std::cout << "ASCII 藝術圖將被輸出到: " << outputPath << std::endl;
    }

    // Execute the jp2a command
    int systemStatus = Jp2a::executeJp2a(jp2aCommand);
    if (systemStatus != 0) {
        std::cerr << "Failed to execute jp2a command." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
