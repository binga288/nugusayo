// include/jp2a.h
#ifndef JP2A_H
#define JP2A_H

#include <string>

namespace Jp2a {
/**
 * @brief Builds the jp2a command string based on terminal size and color
 * option.
 *
 * @param width The width of the terminal.
 * @param height The height available for the image.
 * @param colorful Whether to enable colorful output.
 * @param imageFile The path to the image file.
 * @return std::string The complete jp2a command.
 */
std::string buildJp2aCommand(int width, int height, bool colorful,
                             const std::string& imageFile);

/**
 * @brief Executes the jp2a command.
 *
 * @param command The jp2a command to execute.
 * @return int The exit status of the jp2a command.
 */
int executeJp2a(const std::string& command);
}  // namespace Jp2a

#endif  // JP2A_H
