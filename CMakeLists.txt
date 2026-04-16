cmake_minimum_required(VERSION 3.16)

project(XLedger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON) # qt_standard_project_setup()默认没有开启它
set(CMAKE_AUTOMOC ON)

# 设置ui文件搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)

# 设置安装前缀
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dist")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/xledger.rc")

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Test)
qt_standard_project_setup()


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/presenter 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/dtos  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
)

file(GLOB SOURCES 
    "src/model/*.cpp" 
    "src/model/dtos/*.h"
    "src/view/*.cpp" 
    "src/presenter/*.cpp" 
    "src/database/*.cpp" 
    "src/ui/*.ui" 
)
qt_add_executable(XLedger
    src/main.cpp
    src/view/mainview
    resources.qrc
    ${SOURCES}
    ${app_icon_resource_windows}
)

add_subdirectory(xxun-ui)

enable_testing()
add_subdirectory(tests)

target_include_directories(XLedger
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/xxun-ui
)

target_link_libraries(XLedger PRIVATE Qt6::Widgets Qt6::Sql Qt6::Test xxun-ui)

set_target_properties(XLedger PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS XLedger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
