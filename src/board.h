#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <expected>  // C++23 feature
#include <filesystem>
#include <string>

#include "field.h"

const int BOARD_SIZE = 9;

using Row = std::array<Field, BOARD_SIZE>;
using Column = std::array<Field, BOARD_SIZE>;

class Board {
 private:
  std::array<std::array<Field, BOARD_SIZE>, BOARD_SIZE> fields;

 public:
  std::expected<void, std::string> loadBoard(const std::filesystem::path &path);
  Field getField(const int rowIndex, const int columnIndex) const;
  Row getRow(const int rowIndex) const;
  Column getCol(const int columnIndex) const;
  void print() const;
};

#endif  // BOARD_H
