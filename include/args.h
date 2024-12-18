// include/args.h
#ifndef ARGS_H
#define ARGS_H

#include <algorithm>
#include <string>
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

/**
 * @brief Retrieves the value for a specific argument (e.g., "--path").
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param arg The argument to search for (e.g., "--path").
 * @return std::string The value associated with the argument, or an empty
 * string if not found.
 */
std::string getArgumentValue(int argc, char* argv[], const std::string& arg);
}  // namespace Args

#endif  // ARGS_H
