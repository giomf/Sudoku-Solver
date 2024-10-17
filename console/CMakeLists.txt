set(PROGRAM_CONSOLE_NAME "${PROGRAM_NAME}_console")

add_executable(${PROGRAM_CONSOLE_NAME} src/main.cpp)
target_include_directories(${PROGRAM_CONSOLE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/src")
target_link_libraries(${PROGRAM_CONSOLE_NAME} PRIVATE ${PROGRAM_LIB_NAME} argparse)
