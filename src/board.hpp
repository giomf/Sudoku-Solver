#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <expected>  // C++23 feature
#include <filesystem>
#include <string>
#include <tuple>

#include "constants.hpp"

using RawBoard = std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE>;
using Fields = std::array<int, BOARD_SIZE>;

class Board {
 private:
  std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> board;
  static std::tuple<int, int> getSectionIndexPair(const int index);
  static std::tuple<int, int, int, int> getSectionIndex(const int row,
                                                        const int column);

 public:
  std::expected<void, std::string> loadBoard(
      const std::filesystem::path &filePath);
  std::expected<void, std::string> loadBoard(const std::string &fileContent);
  std::expected<void, std::string> loadBoard(const RawBoard &rawBoard);

  int getField(const int row, const int column) const;
  Fields getRow(const int row) const;
  Fields getColumn(const int column) const;
  Fields getSection(const int row, const int column) const;
  void print() const;
};

#endif  // BOARD_H
