#include <algorithm>
#include <ranges>
#include <vector>

#include "constants.h"
#include "fieldContainer.h"

const std::array<int, BOARD_SIZE> FULL_SET = {1, 2, 3, 4, 5, 6, 7, 8, 9};

std::vector<int> FieldContainer::getCandidates() const {
  std::vector<int> candidates;

  std::transform(fields.begin(), fields.end(), candidates.begin(),
                 [](Field* field) { return field->getValue(); });

  // std::set_difference(FULL_SET.begin(), FULL_SET.end(), fields.begin(),
  //                     fields.end(),
  //                     std::inserter(candidates, candidates.begin()));
  return candidates;
}
