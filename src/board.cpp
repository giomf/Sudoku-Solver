#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>

#include "board.h"
#include "constants.h"

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
  // Set the fields and rows
  for (int row = 0; row < BOARD_SIZE; ++row) {
    std::array<Field *, BOARD_SIZE> rowFields;
    for (int column = 0; column < BOARD_SIZE; ++column) {
      auto field = Field(rawBoard[row][column]);
      board[row][column] = field;
      rowFields[column] = &field;
    }
    rows[row] = Row(rowFields);
  }

  // Set the columns
  for (int column = 0; column < BOARD_SIZE; ++column) {
    std::array<Field *, BOARD_SIZE> columnsFields;
    for (int row = 0; row < BOARD_SIZE; ++row) {
      columnsFields[row] = &board[row][column];
    }
    columns[column] = Column(columnsFields);
  }

  // Set the sections
  int sectionIndex = 0;
  for (int row = 0; row < BOARD_SIZE; row += SECTION_SIZE) {
    for (int column = 0; column < BOARD_SIZE; column += SECTION_SIZE) {
      std::array<Field *, BOARD_SIZE> sectionFields;
      int FieldIndex = 0;
      for (int subRow = 0; subRow < SECTION_SIZE; ++subRow) {
        for (int subColumn = 0; subColumn < SECTION_SIZE; ++subColumn) {
          sectionFields[FieldIndex] = &board[row + subRow][column + subColumn];
          ++FieldIndex;
        }
      }
      FieldIndex = 0;
      sections[sectionIndex] = Section(sectionFields);
      ++sectionIndex;
    }
  }

  return {};
}

Field Board::getField(const int row, const int column) const {
  return board[row][column];
}

Row Board::getRow(const int row) const { return rows[row]; }
Column Board::getColumn(const int column) const { return columns[column]; }

void Board::print() const {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int column = 0; column < BOARD_SIZE; ++column) {
      std::cout << getField(row, column).getValue();
    }
    std::cout << std::endl;
  }
}
