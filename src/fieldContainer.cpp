#include <algorithm>
#include <vector>

#include "constants.hpp"
#include "fieldContainer.hpp"

constexpr std::array<int, BOARD_SIZE> FULL_SET = {1, 2, 3, 4, 5, 6, 7, 8, 9};

std::vector<int> FieldContainer::getCandidates() const {
  std::vector<int> candidates;
  std::vector<int> rawFields(fields.size());

  std::transform(fields.begin(), fields.end(), rawFields.begin(),
                 [](Field* field) { return field->getValue(); });

  std::sort(rawFields.begin(), rawFields.end());
  std::set_difference(FULL_SET.begin(), FULL_SET.end(), rawFields.begin(),
                      rawFields.end(),
                      std::inserter(candidates, candidates.begin()));

  return candidates;
}

Field FieldContainer::getField(const int index) const { return *fields[index]; }
