// src/args.cpp
#include "args.h"

#include <algorithm>
#include <string>

namespace Args {

bool isFlagEnabled(int argc, char* argv[], const std::string& flag) {
    return std::any_of(argv + 1, argv + argc, [&](const char* arg) {
        return std::string(arg) == flag;
    });
}

}  // namespace Args
