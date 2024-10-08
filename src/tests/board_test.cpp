#include <filesystem>

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
    "0,0,0,0,0,0,0,0,0\n";

constexpr RawBoard VALID_RAW_BOARD = {{
    {1, 2, 3, 4, 5, 6, 7, 8, 9},
    {0, 1, 2, 3, 4, 5, 6, 7, 8},
    {0, 0, 1, 2, 3, 4, 5, 6, 7},
    {0, 0, 0, 1, 2, 3, 4, 5, 6},
    {0, 0, 0, 0, 1, 2, 3, 4, 5},
    {0, 0, 0, 0, 0, 1, 2, 3, 4},
    {0, 0, 0, 0, 0, 0, 1, 2, 3},
    {0, 0, 0, 0, 0, 0, 0, 1, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
}};

TEST(BoardTests, loadBoard_FileNotFound) {
  Board board;
  std::filesystem::path fileThatDoesNotExists = "/file/that/does/not/exists";
  ASSERT_FALSE(board.loadBoard(fileThatDoesNotExists));
}

TEST(BoardTests, loadBoard_FieldsSuccessful) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int column = 0; column < BOARD_SIZE; ++column) {
      ASSERT_EQ(VALID_RAW_BOARD[row][column],
                board.getField(row, column).getValue());
    }
  }
}

TEST(BoardTests, loadBoard_RowsSuccessful) {
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int column = 0; column < BOARD_SIZE; ++column) {
      ASSERT_EQ(VALID_RAW_BOARD[row][column],
                board.getRow(row).getField(column).getValue());
    }
  }
}

TEST(BoardTests, loadBoard_ColumnsSuccessful) {
  GTEST_SKIP();
  Board board;
  ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  for (int column = 0; column < BOARD_SIZE; ++column) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
      ASSERT_EQ(VALID_RAW_BOARD[row][column],
                board.getColumn(column).getField(row).getValue());
    }
  }
}

TEST(BoardTests, loadBoard_SectionsSuccessful) {
  GTEST_SKIP();
  // Board board;
  // ASSERT_TRUE(board.loadBoard(VALID_RAW_BOARD));
  // // TODO
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
