#include <fstream>
#include <iostream>
#include <memory>

#include "board.h"

const int CSV_LINE_LENGTH = 17;

std::expected<void, std::string> Board::loadBoard(
    const std::filesystem::path &path) {
  std::ifstream file(path);

  if (!file) {
    return std::unexpected("failed to open file: " + path.string());
  }

  std::string line;
  int lineCount = 0;
  while (std::getline(file, line)) {
    for (int valuePos = 0; valuePos < CSV_LINE_LENGTH; valuePos += 2) {
      fields[lineCount][valuePos / 2] =
          std::make_shared<Field>(line[valuePos] - '0');
    }
    lineCount++;
  }
  file.close();
  return {};
}

std::shared_ptr<Field> Board::getField(const int rowIndex,
                                       const int columnIndex) const {
  return fields[rowIndex][columnIndex];
}

Row Board::getRow(const int rowIndex) const { return fields[rowIndex]; }
Column Board::getColumn(const int columnIndex) const {
  Column column;
  for (int rowIndex = 0; rowIndex < BOARD_SIZE; ++rowIndex) {
    column[rowIndex] = fields[rowIndex][columnIndex];
  }
  return column;
}

void Board::print() const {
  for (int rowIndex = 0; rowIndex < BOARD_SIZE; ++rowIndex) {
    for (int columnIndex = 0; columnIndex < BOARD_SIZE; ++columnIndex) {
      std::cout << getField(rowIndex, columnIndex)->getValue();
    }
    std::cout << std::endl;
  }
}
