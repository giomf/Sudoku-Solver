
#include "board.hpp"
#include "game.hpp"
#include "gtest/gtest.h"

constexpr RawBoard BOARD_1 = {{{3, 0, 9, 4, 0, 7, 5, 0, 8},
                               {7, 0, 6, 0, 0, 5, 0, 0, 0},
                               {4, 0, 2, 6, 0, 3, 1, 9, 0},
                               {9, 7, 4, 1, 3, 0, 0, 0, 0},
                               {2, 0, 0, 0, 0, 0, 7, 0, 0},
                               {8, 3, 0, 7, 6, 0, 0, 1, 9},
                               {0, 0, 0, 0, 7, 0, 0, 2, 6},
                               {0, 0, 7, 0, 0, 0, 0, 5, 0},
                               {1, 0, 0, 0, 0, 6, 4, 7, 3}}};

constexpr RawBoard BOARD_1_SOLVED = {{{3, 1, 9, 4, 2, 7, 5, 6, 8},
                                      {7, 8, 6, 9, 1, 5, 3, 4, 2},
                                      {4, 5, 2, 6, 8, 3, 1, 9, 7},
                                      {9, 7, 4, 1, 3, 2, 6, 8, 5},
                                      {2, 6, 1, 5, 9, 8, 7, 3, 4},
                                      {8, 3, 5, 7, 6, 4, 2, 1, 9},
                                      {5, 4, 3, 8, 7, 1, 9, 2, 6},
                                      {6, 2, 7, 3, 4, 9, 8, 5, 1},
                                      {1, 9, 8, 2, 5, 6, 4, 7, 3}}};

constexpr RawBoard BOARD_2 = {{{0, 0, 0, 0, 0, 5, 0, 8, 4},
                               {0, 0, 1, 9, 0, 6, 0, 0, 0},
                               {0, 4, 9, 7, 2, 0, 6, 0, 3},
                               {0, 0, 5, 2, 0, 9, 0, 0, 0},
                               {9, 2, 0, 4, 7, 0, 0, 0, 1},
                               {0, 6, 3, 5, 0, 1, 0, 2, 0},
                               {1, 0, 0, 6, 0, 0, 0, 0, 2},
                               {0, 8, 4, 0, 5, 0, 0, 9, 6},
                               {0, 9, 6, 0, 1, 0, 7, 0, 5}}};

constexpr RawBoard BOARD_2_SOLVED = {{{6, 7, 2, 1, 3, 5, 9, 8, 4},
                                      {8, 3, 1, 9, 4, 6, 2, 5, 7},
                                      {5, 4, 9, 7, 2, 8, 6, 1, 3},
                                      {4, 1, 5, 2, 6, 9, 3, 7, 8},
                                      {9, 2, 8, 4, 7, 3, 5, 6, 1},
                                      {7, 6, 3, 5, 8, 1, 4, 2, 9},
                                      {1, 5, 7, 6, 9, 4, 8, 3, 2},
                                      {2, 8, 4, 3, 5, 7, 1, 9, 6},
                                      {3, 9, 6, 8, 1, 2, 7, 4, 5}}};

constexpr RawBoard BOARD_3 = {{{0, 0, 0, 0, 1, 0, 0, 0, 4},
                               {3, 8, 0, 0, 9, 4, 2, 5, 0},
                               {4, 0, 0, 8, 7, 2, 6, 1, 3},
                               {9, 3, 0, 0, 8, 0, 7, 4, 5},
                               {5, 0, 7, 0, 0, 9, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 1, 0, 0},
                               {6, 7, 3, 0, 0, 0, 0, 0, 9},
                               {0, 0, 5, 9, 0, 6, 3, 7, 0},
                               {2, 0, 0, 0, 4, 7, 0, 6, 0}}};

constexpr RawBoard BOARD_3_SOLVED = {{{7, 6, 2, 5, 1, 3, 9, 8, 4},
                                      {3, 8, 1, 6, 9, 4, 2, 5, 7},
                                      {4, 5, 9, 8, 7, 2, 6, 1, 3},
                                      {9, 3, 6, 2, 8, 1, 7, 4, 5},
                                      {5, 1, 7, 4, 6, 9, 8, 3, 2},
                                      {8, 2, 4, 7, 3, 5, 1, 9, 6},
                                      {6, 7, 3, 1, 5, 8, 4, 2, 9},
                                      {1, 4, 5, 9, 2, 6, 3, 7, 8},
                                      {2, 9, 8, 3, 4, 7, 5, 6, 1}}};

TEST(GameTests, solve_Board1) {
  Board board;
  ASSERT_TRUE(board.loadBoard(BOARD_1));
  Board expectedBoard;
  ASSERT_TRUE(expectedBoard.loadBoard(BOARD_1_SOLVED));

  Game game(board);
  auto solvedBoard = game.solve();
  ASSERT_EQ(expectedBoard.toString(), solvedBoard.toString());
}

TEST(GameTests, solve_Board2) {
  Board board;
  ASSERT_TRUE(board.loadBoard(BOARD_2));
  Board expectedBoard;
  ASSERT_TRUE(expectedBoard.loadBoard(BOARD_2_SOLVED));

  Game game(board);
  auto solvedBoard = game.solve();
  ASSERT_EQ(expectedBoard.toString(), solvedBoard.toString());
}

TEST(GameTests, solve_Board3) {
  Board board;
  ASSERT_TRUE(board.loadBoard(BOARD_3));
  Board expectedBoard;
  ASSERT_TRUE(expectedBoard.loadBoard(BOARD_3_SOLVED));

  Game game(board);
  auto solvedBoard = game.solve();
  ASSERT_EQ(expectedBoard.toString(), solvedBoard.toString());
}
