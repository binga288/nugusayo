// include/terminal.h
#ifndef TERMINAL_H
#define TERMINAL_H

#include <optional>
#include <string>  // 新增這一行
#include <utility>

namespace Terminal {
/**
 * @brief Executes a shell command and retrieves its output as an integer.
 *
 * @param command The shell command to execute.
 * @return std::optional<int> The output integer if successful, std::nullopt
 * otherwise.
 */
std::optional<int> executeCommand(const std::string& command);

/**
 * @brief Retrieves the terminal size (columns and rows).
 *
 * @return std::optional<std::pair<int, int>> Pair of columns and rows if
 * successful, std::nullopt otherwise.
 */
std::optional<std::pair<int, int>> getTerminalSize();
}  // namespace Terminal

#endif  // TERMINAL_H
