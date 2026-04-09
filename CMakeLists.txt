cmake_minimum_required(VERSION 3.16)

project(XLedger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON) # qt_standard_project_setup()默认没有开启它


# 设置ui文件搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

qt_standard_project_setup()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/view)
file(GLOB SOURCES "src/model/*.cpp" "src/view/*.cpp" "src/presenter/*.cpp" "src/ui/*.ui")
qt_add_executable(XLedger
    src/main.cpp
    resources.qrc
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
