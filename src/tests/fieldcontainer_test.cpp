#include <algorithm>
#include <array>

#include "constants.hpp"
#include "fieldContainer.hpp"
#include "gtest/gtest.h"

TEST(FieldcontainerTests, getCandidates_NoCandidates) {
  Field field0(1), field1(2), field2(3), field3(4), field4(5), field5(6),
      field6(7), field7(8), field8(9);

  const std::array<Field*, BOARD_SIZE> fields = {&field0, &field1, &field2,
                                                 &field3, &field4, &field5,
                                                 &field6, &field7, &field8};
  FieldContainer fieldcontainer(fields);
  auto candidates = fieldcontainer.getCandidates();
  ASSERT_TRUE(candidates.empty());
}

TEST(FieldcontainerTests, getCandidates_AllCandidates) {
  Field field0(0), field1(0), field2(0), field3(0), field4(0), field5(0),
      field6(0), field7(0), field8(0);
  constexpr std::array<int, BOARD_SIZE> result = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  const std::array<Field*, BOARD_SIZE> fields = {&field0, &field1, &field2,
                                                 &field3, &field4, &field5,
                                                 &field6, &field7, &field8};
  FieldContainer fieldcontainer(fields);
  auto candidates = fieldcontainer.getCandidates();
  ASSERT_TRUE(std::equal(result.begin(), result.end(), candidates.begin()));
}

TEST(FieldcontainerTests, getCandidates_SomeCandidates) {
  Field field0(1), field1(2), field2(3), field3(4), field4(0), field5(0),
      field6(0), field7(0), field8(0);
  constexpr std::array<int, 5> result = {5, 6, 7, 8, 9};
  const std::array<Field*, BOARD_SIZE> fields = {&field0, &field1, &field2,
                                                 &field3, &field4, &field5,
                                                 &field6, &field7, &field8};
  FieldContainer fieldcontainer(fields);
  auto candidates = fieldcontainer.getCandidates();
  ASSERT_TRUE(std::equal(result.begin(), result.end(), candidates.begin()));
}
