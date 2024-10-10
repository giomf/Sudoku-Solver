cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "Sudoku Solver")
set(PROGRAM_NAME "ss")
set(PROGRAM_LIB_NAME "${PROGRAM_NAME}_lib")
set(PROGRAM_TEST_NAME "${PROGRAM_NAME}_tests")

# Set the project name and version
project(${PROJECT_NAME} VERSION 1.0)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add libs as a subdirectory
add_subdirectory(libs/spdlog)
add_subdirectory(libs/googletest)
add_subdirectory(libs/argparse)

set(LIB_SOURCES src/board.cpp src/game.cpp)
set(TEST_SOURCES src/tests/main.cpp src/tests/board_test.cpp src/tests/game_test.cpp)

# Add the main executable
add_executable(${PROGRAM_NAME} src/main.cpp)
target_link_libraries(${PROGRAM_NAME} PRIVATE ${PROGRAM_LIB_NAME} argparse)

# Add main Lib
add_library(${PROGRAM_LIB_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROGRAM_LIB_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROGRAM_LIB_NAME} PUBLIC spdlog::spdlog)

# Add the test executable
add_executable(${PROGRAM_TEST_NAME} ${TEST_SOURCES})
target_include_directories(${PROGRAM_TEST_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROGRAM_TEST_NAME} PRIVATE ${PROGRAM_LIB_NAME} gtest)

# Enable testing
enable_testing()
