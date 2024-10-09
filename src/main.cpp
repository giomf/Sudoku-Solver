#include <spdlog/spdlog.h>

#include <argparse/argparse.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "board.hpp"
#include "game.hpp"

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

int main(int argc, char* argv[]) {
  setLogLevel();

  argparse::ArgumentParser program("Sudoku Solver");

  program.add_argument("--field").help("The field to be loaded").required();
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

  auto inputFile = program.get<std::string>("--field");
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
    std::cout << "Read board: \n" << board.toString() << std::endl;
  }
  Game game(board);
  board = game.solve();
  if (print == true) {
    std::cout << "Solved board: \n" << board.toString() << std::endl;
  }

  if (program.present("--write")) {
    auto outputFile = program.get<std::string>("--write");
    auto writeResult =
        writeFile(std::filesystem::path(outputFile), board.toString());
    std::cout << "Solved board written to " << outputFile << std::endl;
    if (!writeResult) {
      std::cerr << writeResult.error() << std::endl;
      return 1;
    }
  }

  return 0;
}
