set(PROGRAM_TEST_NAME "${PROGRAM_NAME}_tests")
set(TEST_SOURCES src/main.cpp src/board_test.cpp src/game_test.cpp)

# add_dependencies(${PROGRAM_TEST_NAME} ${PROGRAM_LIB_NAME})
message("LIB_NAME_IN_TEST: ${PROGRAM_LIB_NAME}")

add_executable(${PROGRAM_TEST_NAME} ${TEST_SOURCES})
target_include_directories(${PROGRAM_TEST_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/src")
target_link_libraries(${PROGRAM_TEST_NAME} PRIVATE ${PROGRAM_LIB_NAME} gtest)
