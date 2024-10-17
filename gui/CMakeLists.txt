set(PROGRAM_GUI_NAME "${PROGRAM_NAME}_gui")

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROGRAM_GUI_NAME} src/main.cpp)
target_link_libraries(${PROGRAM_GUI_NAME} PRIVATE Qt6::Quick ${PROGRAM_LIB_NAME})
target_include_directories(${PROGRAM_GUI_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/src")
qt_add_qml_module(${PROGRAM_GUI_NAME}
    URI sudoku-solver
    VERSION 1.0
    QML_FILES
        Main.qml
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROGRAM_GUI_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROGRAM_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROGRAM_GUI_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
