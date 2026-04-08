cmake_minimum_required(VERSION 3.16)

project(XLedger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON) 

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

qt_standard_project_setup()




include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ui)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h" "*.qrc")
qt_add_executable(XLedger
    ${SOURCES}
)

add_subdirectory(xxun-ui)

target_include_directories(XLedger
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/xxun-ui
)

target_link_libraries(XLedger PRIVATE Qt6::Widgets Qt6::Sql xxun-ui)

set_target_properties(XLedger PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS XLedger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
