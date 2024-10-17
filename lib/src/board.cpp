#include <spdlog/spdlog.h>

#include <iostream>
#include <sstream>
#include <string>

#include "board.hpp"
#include "constants.hpp"

namespace {

struct SectionPosition {
  int begin;
  int end;
};

/**
 * @brief Computes the section index pair (begin and end) for a given index.
 *
 * Sections refer to 3x3 grids within the board. This function helps map board
 * indices to section indices.
 *
 * @param index The row or column index to map.
 * @return A tuple containing the begin and end indices for the section.
 */
SectionPosition getSectionPosition(const int index) {
  int begin = (index / SECTION_COUNT) * SECTION_SIZE;
  int end = begin + SECTION_SIZE;

  return {begin = begin, end = end};
}

}  // namespace

std::expected<void, std::string> Board::loadBoard(
    const std::string &fileContent) {
  if (fileContent.length() != CSV_FILE_SIZE) {
    return std::unexpected(
        "Error: failed to parse board. Wrong Content length of" +
        std::to_string(fileContent.length()));
  }

  RawBoard rawBoard;
  int row = 0, column = 0;
  bool lastCharacterValue = false;

  // Parse the board
  for (char character : fileContent) {
    if (character >= '0' && character <= '9' && (!lastCharacterValue)) {
      rawBoard[row][column] = (character - '0');
      lastCharacterValue = true;
      ++column;
    } else if (character == '\n' && (lastCharacterValue)) {
      lastCharacterValue = false;
      ++row;
      column = 0;
    } else if (character == ',' && (lastCharacterValue)) {
      lastCharacterValue = false;
    } else {
      spdlog::debug(
          "\nRow: {}\nColumn: {}\nCharacter: {}\nLastCharacterWasValue: {}",
          row, column, character, lastCharacterValue);
      return std::unexpected("Error: failed to parse board");
    }
  }

  return loadBoard(rawBoard);
}

std::expected<void, std::string> Board::loadBoard(const RawBoard &rawBoard) {
  board = rawBoard;
  return {};
}

int Board::getField(const int row, const int column) const {
  return board[row][column];
}
void Board::setField(const int row, const int column, const int value) {
  board[row][column] = value;
}

Fields Board::getRow(const int row) const { return board[row]; }

Fields Board::getColumn(const int columnIndex) const {
  Fields column;
  for (int rowIndex = 0; rowIndex < ROW_COLUMN_LENGTH; ++rowIndex) {
    column[rowIndex] = board[rowIndex][columnIndex];
  }
  return column;
}

Fields Board::getSection(const int row, const int column) const {
  auto [rowBegin, rowEnd] = getSectionPosition(row);
  auto [columnBegin, columnEnd] = getSectionPosition(column);
  Fields section;
  int index = 0;
  for (int rowIndex = rowBegin; rowIndex < rowEnd; ++rowIndex) {
    for (int columnIndex = columnBegin; columnIndex < columnEnd;
         ++columnIndex) {
      section[index] = board[rowIndex][columnIndex];
      ++index;
    }
  }

  return section;
}

std::string Board::toCSVString() const {
  std::stringstream ss;
  for (int row = 0; row < ROW_COLUMN_LENGTH; ++row) {
    for (int column = 0; column < ROW_COLUMN_LENGTH; ++column) {
      ss << getField(row, column);
      if (column < ROW_COLUMN_LENGTH - 1) {
        ss << ',';
      }
    }
    ss << '\n';
  }
  return ss.str();
}
