// src/args.cpp
#include "args.h"

namespace Args {

bool isFlagEnabled(int argc, char* argv[], const std::string& flag) {
    return std::find(argv, argv + argc, flag) != (argv + argc);
}

std::string getArgumentValue(int argc, char* argv[], const std::string& arg) {
    for (int i = 0; i < argc - 1; ++i) {
        if (std::string(argv[i]) == arg) {
            return std::string(argv[i + 1]);
        }
    }
    return "";
}

}  // namespace Args
