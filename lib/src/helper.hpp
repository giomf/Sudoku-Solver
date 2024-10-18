#include <expected>
#include <filesystem>
#include <string>

/**
 * @brief Sets the log level for the application based on the `LOG_LEVEL`
 * environment variable.
 *
 * This function reads the `LOG_LEVEL` environment variable and adjusts the
 * logging level for the application. If the variable is not set or is invalid,
 * it defaults to 'info'. Supported log levels: debug, info, warn, error,
 * critical, off.
 */
void setLogLevel();

/**
 * @brief Loads the content of a file into a string.
 *
 * This function reads the content of the file at the given file path and
 * returns it as a string. If the file cannot be opened, an error message is
 * returned.
 *
 * @param filePath The path to the file to be loaded.
 * @return A string containing the file's contents if successful, or an error
 * message on failure.
 */
std::expected<std::string, std::string> loadFile(
    const std::filesystem::path& filePath);

/**
 * @brief Writes content to a file at the specified file path.
 *
 * This function writes the provided content to the file at the given file path.
 * If the file cannot be opened, an error message is returned.
 *
 * @param filePath The path to the file where content will be written.
 * @param content The content to write to the file.
 * @return void on success, or an error message on failure.
 */
std::expected<void, std::string> writeFile(
    const std::filesystem::path& filePath, std::string content);
