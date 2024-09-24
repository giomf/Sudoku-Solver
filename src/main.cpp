#include <iostream>
#include <string>

#include "board.h"

const std::string boardPath = "./field.csv";

int main() {
  Board board;
  auto result = board.loadBoard(boardPath);
  if (!result) {
    std::cerr << result.error() << std::endl;
    return 1;
  }
  board.print();

  return 0;
}
