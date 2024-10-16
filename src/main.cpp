#include <spdlog/spdlog.h>

#include <argparse/argparse.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "board.hpp"
#include "game.hpp"

/**
 * @brief Sets the log level for the application based on the `LOG_LEVEL`
 * environment variable.
 *
 * This function reads the `LOG_LEVEL` environment variable and adjusts the
 * logging level for the application. If the variable is not set or is invalid,
 * it defaults to 'info'. Supported log levels: debug, info, warn, error,
 * critical, off.
 */
void setLogLevel() {
  const char* logLevel = std::getenv("LOG_LEVEL");

  // Set the log level based on the environment variable
  if (logLevel) {
    if (std::string(logLevel) == "debug") {
      spdlog::set_level(spdlog::level::debug);
    } else if (std::string(logLevel) == "info") {
      spdlog::set_level(spdlog::level::info);
    } else if (std::string(logLevel) == "warn") {
      spdlog::set_level(spdlog::level::warn);
    } else if (std::string(logLevel) == "error") {
      spdlog::set_level(spdlog::level::err);
    } else if (std::string(logLevel) == "critical") {
      spdlog::set_level(spdlog::level::critical);
    } else {
      spdlog::set_level(spdlog::level::off);  // Default to off if invalid
    }
  } else {
    spdlog::set_level(spdlog::level::info);  // Default log level
  }
}

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
    const std::filesystem::path& filePath) {
  std::ifstream file(filePath);

  if (!file) {
    return std::unexpected("Error: failed to open file: " + filePath.string());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

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
    const std::filesystem::path& filePath, std::string content) {
  std::ofstream file(filePath);

  if (!file) {
    return std::unexpected("Error: failed to open file: " + filePath.string());
  }

  file << content;
  file.close();
  return {};
}

/**
 * @brief The main function of the Sudoku Solver program.
 *
 * This function sets up the command-line argument parser, loads a Sudoku puzzle
 * from a file, solves the puzzle, and either prints the solved board to the
 * console or writes it to a file depending on the command-line arguments
 * provided.
 *
 * Command-line arguments:
 * - `--board <path>`: The path to the Sudoku puzzle file (required).
 * - `--print`: Prints the loaded and solved board to the console.
 * - `--write <path>`: Writes the solved board to the specified file.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 on success, or 1 on error.
 */
int main(int argc, char* argv[]) {
  setLogLevel();

  argparse::ArgumentParser program("Sudoku Solver");

  program.add_argument("--board").help("The board to be loaded").required();
  auto& group = program.add_mutually_exclusive_group(true);
  group.add_argument("--print")
      .help("Prints the loaded and solved board")
      .flag();
  group.add_argument("--write").help("Writes the solved board to a file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  auto inputFile = program.get<std::string>("--board");
  auto print = program["--print"];

  auto fileResult = loadFile(std::filesystem::path(inputFile));
  if (!fileResult) {
    std::cerr << fileResult.error() << std::endl;
    return 1;
  }

  Board board;
  auto loadResult = board.loadBoard(fileResult.value());
  if (!loadResult) {
    std::cerr << loadResult.error() << std::endl;
    return 1;
  }

  if (print == true) {
    std::cout << "Read board: \n" << board.toCSVString() << std::endl;
  }
  Game game(board);
  board = game.solve();
  if (print == true) {
    std::cout << "Solved board: \n" << board.toCSVString() << std::endl;
  }

  if (program.present("--write")) {
    auto outputFile = program.get<std::string>("--write");
    auto writeResult =
        writeFile(std::filesystem::path(outputFile), board.toCSVString());
    std::cout << "Solved board written to " << outputFile << std::endl;
    if (!writeResult) {
      std::cerr << writeResult.error() << std::endl;
      return 1;
    }
  }

  return 0;
}
