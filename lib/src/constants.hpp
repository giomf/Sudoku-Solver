#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MAX_SOLVE_ITERATIONS = 100;
constexpr int EMPTY_FIELD = 0;

constexpr int SECTION_SIZE = 3;
constexpr int SECTION_COUNT = 3;
constexpr int ROW_COLUMN_LENGTH = SECTION_COUNT * SECTION_SIZE;

constexpr int CSV_LINE_LENGTH = ROW_COLUMN_LENGTH * 2 - 1;
constexpr int CSV_FILE_SIZE = CSV_LINE_LENGTH * (ROW_COLUMN_LENGTH + 1);

#endif  // CONSTANTS_H
