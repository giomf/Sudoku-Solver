#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <expected>  // C++23 feature
#include <filesystem>
#include <string>

#include "constants.hpp"
#include "field.hpp"
#include "fieldContainer.hpp"

using Row = FieldContainer;
using Column = FieldContainer;
using Section = FieldContainer;
using RawBoard = std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE>;

class Board {
 private:
  std::array<std::array<Field, BOARD_SIZE>, BOARD_SIZE> board;
  std::array<FieldContainer, BOARD_SIZE> rows;
  std::array<FieldContainer, BOARD_SIZE> columns;
  std::array<FieldContainer, BOARD_SIZE> sections;

 public:
  std::expected<void, std::string> loadBoard(
      const std::filesystem::path &filePath);
  std::expected<void, std::string> loadBoard(const std::string &fileContent);
  std::expected<void, std::string> loadBoard(const RawBoard &rawBoard);

  Field getField(const int row, const int column) const;
  Row getRow(const int row) const;
  Column getColumn(const int column) const;
  void print() const;
};

#endif  // BOARD_H
