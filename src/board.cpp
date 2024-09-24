#include <fstream>
#include <iostream>

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
      fields[lineCount][valuePos / 2] = Field(line[valuePos] - '0');
    }
    lineCount++;
  }
  file.close();
  return {};
}

Field Board::getField(const int rowIndex, const int columnIndex) const {
  return fields[rowIndex][columnIndex];
}

Row Board::getRow(const int rowIndex) const { return fields[rowIndex]; }
Row Board::getCol(const int columnIndex) const {
  Column column;
  for (int rowIndex = 0; rowIndex < BOARD_SIZE; rowIndex++) {
    column[rowIndex] = fields[rowIndex][columnIndex];
  }
  return column;
}

void Board::print() const {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      std::cout << getField(row, col).getValue();
    }
    std::cout << std::endl;
  }
}
