#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "board.hpp"
#include "game.hpp"

const std::filesystem::path BOARD_PATH = "./field.csv";

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

int main() {
  setLogLevel();

  Board board;
  auto result = board.loadBoard(BOARD_PATH);
  if (!result) {
    std::cerr << result.error() << std::endl;
    return 1;
  }

  std::cout << "Read board: \n" << board.toString() << std::endl;
  Game game(board);
  board = game.solve();
  std::cout << "Solved board: \n" << board.toString() << std::endl;

  return 0;
}
