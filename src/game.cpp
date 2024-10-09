#include <algorithm>

#include "constants.hpp"
#include "game.hpp"
#include "spdlog/spdlog.h"

constexpr Fields ALL_CANDIDATES{1, 2, 3, 4, 5, 6, 7, 8, 9};

Board Game::solve() {
  bool done = true;
  int iterations = 0;
  do {
    done = true;
    spdlog::debug("Starting Iteration: {}", iterations);
    for (int rowIndex = 0; rowIndex < BOARD_SIZE; ++rowIndex) {
      for (int columnIndex = 0; columnIndex < BOARD_SIZE; ++columnIndex) {
        auto field = board.getField(rowIndex, columnIndex);
        if (field == 0) {
          auto row = board.getRow(rowIndex);
          auto column = board.getColumn(columnIndex);
          auto section = board.getSection(rowIndex, columnIndex);
          auto rowCandidates = Game::getCandidates(row);
          auto columnCandidates = Game::getCandidates(column);
          auto sectionCandidates = Game::getCandidates(section);
          auto matchingCandidates = Game::getMatchingCandidates(
              rowCandidates, columnCandidates, sectionCandidates);

          // Unique match solver
          if (matchingCandidates.size() == 1) {
            spdlog::debug("Solving {}:{} -> {}", rowIndex, columnIndex,
                          matchingCandidates[0]);
            board.setField(rowIndex, columnIndex, matchingCandidates[0]);
          } else {
            done = false;
          }
        }
      }
    }
    ++iterations;
  } while (!done && iterations < MAX_SOLVE_ITERATIONS);
  return board;
}

std::vector<int> Game::getCandidates(Fields fields) {
  std::vector<int> candidates;

  std::sort(fields.begin(), fields.end());
  std::set_difference(ALL_CANDIDATES.begin(), ALL_CANDIDATES.end(),
                      fields.begin(), fields.end(),
                      std::inserter(candidates, candidates.begin()));
  return candidates;
}

std::vector<int> Game::getMatchingCandidates(std::vector<int> a,
                                             std::vector<int> b,
                                             std::vector<int> c) {
  std::vector<int> matches;
  std::vector<int> tempMatches;
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());

  std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                        std::inserter(tempMatches, tempMatches.begin()));

  std::set_intersection(tempMatches.begin(), tempMatches.end(), c.begin(),
                        c.end(), std::inserter(matches, matches.begin()));
  return matches;
}
