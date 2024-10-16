
#include "board.hpp"
#include "constants.hpp"
#include "gtest/gtest.h"

const std::string VALID_FILE_CONTENT =
    "1,2,3,4,5,6,7,8,9\n"
    "0,1,2,3,4,5,6,7,8\n"
    "0,0,1,2,3,4,5,6,7\n"
    "0,0,0,1,2,3,4,5,6\n"
    "0,0,0,0,1,2,3,4,5\n"
    "0,0,0,0,0,1,2,3,4\n"
    "0,0,0,0,0,0,1,2,3\n"
    "0,0,0,0,0,0,0,1,2\n"
    "0,0,0,0,0,0,0,0,1\n";

constexpr RawBoard VALID_RAW_BOARD = {{
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8},
    {0, 0, 1, 2, 3, 4, 5, 6, 7},
    {0, 0, 0, 1, 2, 3, 4, 5, 6},
    {0, 0, 0, 0, 1, 2, 3, 4, 5},
    {0, 0, 0, 0, 0, 1, 2, 3, 4},
    {0, 0, 0, 0, 0, 0, 1, 2, 3},
    {0, 0, 0, 0, 0, 0, 0, 1, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 1},
}};

TEST(BoardTests, loadBoard_FieldsSuccessful) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  for (int row = 0; row < ROW_COLUMN_LENGTH; ++row) {
    for (int column = 0; column < ROW_COLUMN_LENGTH; ++column) {
      ASSERT_EQ(VALID_RAW_BOARD[row][column], board.getField(row, column));
    }
  }
}

TEST(BoardTests, loadBoard_ParsingFailed_ContentLengthToLong) {
  Board board;
  std::string invalidBoard = VALID_FILE_CONTENT + "4,4,4,4,4,4,4,4,4\n";

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, loadBoard_ParsingFailed_ContentLengthToShort) {
  Board board;
  std::string invalidBoard =
      VALID_FILE_CONTENT.substr(0, VALID_FILE_CONTENT.length() - 10);

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, loadBoard_ParsingFailed_TwoValues) {
  Board board;
  std::string invalidBoard = VALID_FILE_CONTENT;
  invalidBoard.insert(5, "4");

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, loadBoard_ParsingFailed_TwoSeperators) {
  Board board;
  std::string invalidBoard = VALID_FILE_CONTENT;
  invalidBoard.insert(5, ",");

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, loadBoard_ParsingFailed_StartingWithSeperators) {
  Board board;
  std::string invalidBoard = VALID_FILE_CONTENT;
  invalidBoard.insert(0, ",");

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, loadBoard_ParsingFailed_InvalidValue) {
  Board board;
  std::string invalidBoard = VALID_FILE_CONTENT;
  invalidBoard.insert(1, "A");

  ASSERT_FALSE(board.loadBoard(invalidBoard));
}

TEST(BoardTests, getRow) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));

  auto result = board.getRow(0);
  Fields expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_TRUE(std::equal(expected.begin(), expected.end(), result.begin()));
}

TEST(BoardTests, getColumn) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  auto result = board.getColumn(4);
  Fields expected{5, 4, 3, 2, 1, 0, 0, 0, 0};
  ASSERT_TRUE(std::equal(expected.begin(), expected.end(), result.begin()));
}

TEST(BoardTests, getSection) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));

  auto result = board.getSection(0, 0);
  Fields expected{1, 2, 3, 0, 1, 2, 0, 0, 1};
  ASSERT_EQ(expected, result);

  result = board.getSection(8, 8);
  expected = {1, 2, 3, 0, 1, 2, 0, 0, 1};
  ASSERT_EQ(expected, result);

  result = board.getSection(4, 4);
  expected = {1, 2, 3, 0, 1, 2, 0, 0, 1};
  ASSERT_EQ(expected, result);

  result = board.getSection(0, 8);
  expected = {7, 8, 9, 6, 7, 8, 5, 6, 7};
  ASSERT_EQ(expected, result);
}
