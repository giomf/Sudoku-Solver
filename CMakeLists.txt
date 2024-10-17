cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Sudoku Solver")
set(PROGRAM_NAME "ss")

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)
# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add libs as a subdirectory
add_subdirectory(3dparty/spdlog)
add_subdirectory(3dparty/googletest)
add_subdirectory(3dparty/argparse)
add_subdirectory(lib)
add_subdirectory(console)
add_subdirectory(gui)
add_subdirectory(tests)
