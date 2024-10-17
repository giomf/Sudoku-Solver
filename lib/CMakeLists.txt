set(PROGRAM_LIB_NAME "${PROGRAM_NAME}_lib" CACHE STRING "") 
set(LIB_SOURCES src/board.cpp src/game.cpp src/helper.cpp)

add_library(${PROGRAM_LIB_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(${PROGRAM_LIB_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${PROGRAM_LIB_NAME} PUBLIC spdlog::spdlog)
