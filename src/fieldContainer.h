#ifndef FIELDCONTAINER_H
#define FIELDCONTAINER_H

#include <array>
#include <vector>

#include "constants.h"
#include "field.h"

class FieldContainer {
 private:
  std::array<Field*, BOARD_SIZE> fields;

 public:
  FieldContainer() {};
  FieldContainer(std::array<Field*, BOARD_SIZE> fields) : fields(fields) {};
  std::vector<int> getCandidates() const;
};

#endif  // FIELDCONTAINER_H
