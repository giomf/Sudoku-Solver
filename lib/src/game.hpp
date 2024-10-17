#ifndef GAME_H
#define GAME_H

#include "board.hpp"

/**
 * @brief The Game class represents the Sudoku solving logic.
 *
 * This class provides methods for solving a Sudoku puzzle by utilizing
 * the Board class and performing candidate analysis on rows, columns, and
 * sections.
 */
class Game {
 private:
  Board board; /**< The current state of the Sudoku board being solved. */

 public:
  /**
   * @brief Constructs a new Game object.
   *
   * Initializes the Game with a given board to solve.
   *
   * @param board The Board object representing the Sudoku puzzle to be solved.
   */
  Game(Board board) : board(board) {}

  /**
   * @brief Solves the Sudoku puzzle.
   *
   * This method iterates through the board, checking each empty field
   * (represented by 0) and attempting to fill it with a valid value based on
   * the row, column, and section candidates. The process continues until no
   * more changes can be made or a maximum number of iterations is reached.
   *
   * @return The solved Board object, or the current state if unsolvable within
   * the iteration limit.
   */
  Board solve();
};

#endif  // GAME_H
