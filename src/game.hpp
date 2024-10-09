#ifndef GAME_H
#define GAME_H

#include <vector>

#include "board.hpp"

class Game {
 private:
  Board board;
  static std::vector<int> getCandidates(Fields fields);
  static std::vector<int> getMatchingCandidates(std::vector<int> a,
                                                std::vector<int> b,
                                                std::vector<int> c);

 public:
  Game(Board board) : board(board) {};
  Board solve();
};

#endif  // GAME_H
