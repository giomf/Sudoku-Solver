#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "board.hpp"
#include "constants.hpp"

std::expected<void, std::string> Board::loadBoard(
    const std::filesystem::path &filePath) {
  std::ifstream file(filePath);

  if (!file) {
    return std::unexpected("Error: failed to open file: " + filePath.string());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  const auto fileContent = buffer.str();
  spdlog::debug("File content:\n{}", fileContent);
  return loadBoard(fileContent);
}

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
  for (int rowIndex = 0; rowIndex < BOARD_SIZE; ++rowIndex) {
    column[rowIndex] = board[rowIndex][columnIndex];
  }
  return column;
}

Fields Board::getSection(const int row, const int column) const {
  auto [rowBegin, rowEnd, columnBegin, columnEnd] =
      Board::getSectionIndex(row, column);
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

std::tuple<int, int, int, int> Board::getSectionIndex(const int row,
                                                      const int column) {
  auto [rowBegin, rowEnd] = Board::getSectionIndexPair(row);
  auto [columnBegin, columnEnd] = Board::getSectionIndexPair(column);
  return std::make_tuple(rowBegin, rowEnd, columnBegin, columnEnd);
}

std::tuple<int, int> Board::getSectionIndexPair(const int index) {
  int begin = 0, end = 0;

  if (index >= SECTION_INDEX_1 && index < SECTION_INDEX_2) {
    begin = SECTION_INDEX_1;
    end = SECTION_INDEX_2;
  } else if (index <= SECTION_INDEX_1) {
    begin = 0;
    end = SECTION_INDEX_1;
  } else {
    begin = SECTION_INDEX_2;
    end = SECTION_INDEX_3;
  }

  return std::make_tuple(begin, end);
}

std::string Board::toString() const {
  std::stringstream ss;
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int column = 0; column < BOARD_SIZE; ++column) {
      ss << getField(row, column);
      if (column < BOARD_SIZE - 1) {
        ss << ',';
      }
    }
    ss << '\n';
  }
  return ss.str();
}
