// main.cpp
#include <cstdlib>
#include <iostream>

#include "args.h"
#include "display.h"
#include "jp2a.h"
#include "terminal.h"

// Constants
constexpr int HEADER_HEIGHT = 7;
constexpr const char* IMAGE_FILE = "images.png";

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    bool colorful = Args::isFlagEnabled(argc, argv, "--colorful");

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

    // Build and execute the jp2a command
    std::string jp2aCommand =
        Jp2a::buildJp2aCommand(termCols, jp2aHeight, colorful, IMAGE_FILE);
    int systemStatus = Jp2a::executeJp2a(jp2aCommand);
    if (systemStatus != 0) {
        std::cerr << "Failed to execute jp2a command." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
