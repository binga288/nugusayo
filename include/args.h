// include/args.h
#ifndef ARGS_H
#define ARGS_H

#include <algorithm>
#include <string>  // 如果使用了 std::string
#include <vector>

namespace Args {
/**
 * @brief Checks if a specific flag is present in the command-line arguments.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param flag The flag to search for (e.g., "--colorful").
 * @return true If the flag is present.
 * @return false Otherwise.
 */
bool isFlagEnabled(int argc, char* argv[], const std::string& flag);
}  // namespace Args

#endif  // ARGS_H
