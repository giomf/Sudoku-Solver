cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "Sudoku Solver")
set(EXECUTABLE_NAME "ss")

# Set the project name and version
project(${PROJECT_NAME} VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add the executable
add_executable(${EXECUTABLE_NAME} src/main.cpp src/board.cpp)
target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
