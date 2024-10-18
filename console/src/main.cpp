#include <argparse/argparse.hpp>
#include <filesystem>
#include <iostream>
#include <string>

#include "board.hpp"
#include "game.hpp"
#include "helper.hpp"

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
