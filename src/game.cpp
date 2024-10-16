#include <vector>

#include "constants.hpp"
#include "game.hpp"
#include "spdlog/spdlog.h"

using Candidates = std::vector<int>;

constexpr Fields ALL_CANDIDATES{1, 2, 3, 4, 5, 6, 7, 8, 9};

namespace {
/**
 * @brief Retrieves the possible candidates for an empty field based on the
 * provided values.
 *
 * This method determines which numbers are missing from a row, column, or
 * section, returning the numbers that could potentially be placed in an empty
 * field.
 *
 * @param fields An array representing either a row, column, or section of the
 * board.
 * @return A vector containing the numbers that are valid candidates for the
 * empty field.
 */

Candidates getCandidates(Fields& fields) {
  std::vector<int> candidates;

  std::sort(fields.begin(), fields.end());
  std::set_difference(ALL_CANDIDATES.begin(), ALL_CANDIDATES.end(),
                      fields.begin(), fields.end(),
                      std::inserter(candidates, candidates.begin()));
  return candidates;
}

/**
 * @brief Finds the common candidates among the row, column, and section.
 *
 * This method computes the intersection of possible candidates from a row,
 * column, and section to determine which values are valid for a particular
 * empty field.
 *
 * @param a Candidates from the row.
 * @param b Candidates from the column.
 * @param c Candidates from the section.
 * @return A vector containing the common candidates that can be placed in the
 * empty field.
 */
Candidates getMatchingCandidates(Candidates& row, Candidates& column,
                                 Candidates& section) {
  Candidates matches;
  Candidates tempMatches;
  std::sort(row.begin(), row.end());
  std::sort(column.begin(), column.end());
  std::sort(section.begin(), section.end());

  std::set_intersection(row.begin(), row.end(), column.begin(), column.end(),
                        std::inserter(tempMatches, tempMatches.begin()));

  std::set_intersection(tempMatches.begin(), tempMatches.end(), section.begin(),
                        section.end(), std::inserter(matches, matches.begin()));
  return matches;
}
};  // namespace

Board Game::solve() {
  bool done = true;
  int iterations = 0;
  do {
    done = true;
    spdlog::debug("Starting Iteration: {}", iterations);
    for (int rowIndex = 0; rowIndex < ROW_COLUMN_LENGTH; ++rowIndex) {
      for (int columnIndex = 0; columnIndex < ROW_COLUMN_LENGTH;
           ++columnIndex) {
        auto field = board.getField(rowIndex, columnIndex);
        if (field == EMPTY_FIELD) {
          auto row = board.getRow(rowIndex);
          auto column = board.getColumn(columnIndex);
          auto section = board.getSection(rowIndex, columnIndex);
          auto rowCandidates = getCandidates(row);
          auto columnCandidates = getCandidates(column);
          auto sectionCandidates = getCandidates(section);
          auto matchingCandidates = getMatchingCandidates(
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
