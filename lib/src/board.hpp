#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <expected>  // C++23 feature
#include <string>

#include "constants.hpp"

using RawBoard =
    std::array<std::array<int, ROW_COLUMN_LENGTH>, ROW_COLUMN_LENGTH>;
using Fields = std::array<int, ROW_COLUMN_LENGTH>;

/**
 * @brief The Board class represents a Sudoku board and provides methods for
 * loading, accessing, and modifying the board.
 */
class Board {
 private:
  RawBoard board; /**< The 9x9 Sudoku board represented as a 2D array */

 public:
  /**
   * @brief Loads a Sudoku board from a file content string.
   *
   * The file content should represent the Sudoku board in CSV format. This
   * method validates the content and loads it into the board structure.
   *
   * @param fileContent The string containing the CSV representation of the
   * Sudoku board.
   * @return std::expected<void, std::string> Void on success, or an error
   * message on failure.
   */
  std::expected<void, std::string> loadBoard(const std::string &fileContent);

  /**
   * @brief Loads a Sudoku board from a `RawBoard` object.
   *
   * This method directly loads a pre-parsed `RawBoard` into the board.
   *
   * @param rawBoard The 2D array representing the Sudoku board.
   * @return std::expected<void, std::string> Void on success, or an error
   * message on failure.
   */
  std::expected<void, std::string> loadBoard(const RawBoard &rawBoard);

  /**
   * @brief Retrieves the value of a specific field on the board.
   *
   * @param row The row index (0-8).
   * @param column The column index (0-8).
   * @return The value of the field at the specified row and column.
   */
  int getField(const int row, const int column) const;

  /**
   * @brief Sets the value of a specific field on the board.
   *
   * @param row The row index (0-8).
   * @param column The column index (0-8).
   * @param value The value to set in the specified field.
   */
  void setField(const int row, const int column, const int value);

  /**
   * @brief Retrieves all values in a specific row.
   *
   * @param row The row index (0-8).
   * @return An array representing the values in the specified row.
   */
  Fields getRow(const int row) const;

  /**
   * @brief Retrieves all values in a specific column.
   *
   * @param column The column index (0-8).
   * @return An array representing the values in the specified column.
   */
  Fields getColumn(const int column) const;

  /**
   * @brief Retrieves all values in the 3x3 section that contains the specified
   * row and column.
   *
   * @param row The row index (0-8).
   * @param column The column index (0-8).
   * @return An array representing the values in the 3x3 section.
   */
  Fields getSection(const int row, const int column) const;

  /**
   * @brief Converts the board to a string in CSV format.
   *
   * Each row is separated by a newline character, and each field in a row is
   * separated by a comma.
   *
   * @return A string representing the board in CSV format.
   */
  std::string toCSVString() const;
};

#endif  // BOARD_H
