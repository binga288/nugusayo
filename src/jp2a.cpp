// src/jp2a.cpp
#include "jp2a.h"

#include <cstdlib>
#include <string>

namespace Jp2a {

std::string buildJp2aCommand(int width, int height, bool colorful,
                             const std::string& imageFile) {
    std::string command = "jp2a --width=" + std::to_string(width) +
                          " --height=" + std::to_string(height);
    if (colorful) {
        command += " --color";
    }
    command += " " + imageFile;
    return command;
}

int executeJp2a(const std::string& command) { return system(command.c_str()); }

}  // namespace Jp2a
