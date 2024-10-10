#ifndef GAME_H
#define GAME_H

#include <vector>

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

  /**
   * @brief Retrieves the possible candidates for an empty field based on the
   * provided values.
   *
   * This method determines which numbers are missing from a row, column, or
   * section, returning the numbers that could potentially be placed in an empty
   * field.
   *
   * @param fields An array representing either a row, column, or section of the
   * board.
   * @return A vector containing the numbers that are valid candidates for the
   * empty field.
   */
  static std::vector<int> getCandidates(Fields fields);

  /**
   * @brief Finds the common candidates among the row, column, and section.
   *
   * This method computes the intersection of possible candidates from a row,
   * column, and section to determine which values are valid for a particular
   * empty field.
   *
   * @param a Candidates from the row.
   * @param b Candidates from the column.
   * @param c Candidates from the section.
   * @return A vector containing the common candidates that can be placed in the
   * empty field.
   */
  static std::vector<int> getMatchingCandidates(std::vector<int> a,
                                                std::vector<int> b,
                                                std::vector<int> c);

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
