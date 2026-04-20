cmake_minimum_required(VERSION 3.16)

project(XLedger VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)
option(BUILD_TEST "Build tests" OFF)

# 设置安装前缀
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/dist")

set(app_icon_resource_windows
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/xledger.rc"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Test)

qt_standard_project_setup()

# =========================================================
# 1. CORE LIBRARY（model + presenter + database）
# =========================================================

file(GLOB XLEDGER_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/service/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/presenter/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp

)

file(GLOB XLEDGER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.cpp
)


qt_add_library(xledger_core STATIC ${XLEDGER_CORE_SOURCES})

target_include_directories(xledger_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/service
    ${CMAKE_CURRENT_SOURCE_DIR}/src/model/dtos
    ${CMAKE_CURRENT_SOURCE_DIR}/src/presenter
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interface/view
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interface/model
)

add_subdirectory(xxun-ui)



target_link_libraries(xledger_core PUBLIC
    Qt::Widgets
    Qt::Core
    Qt::Sql
)

# =========================================================
# 2. APP（只放 view + main）
# =========================================================

qt_add_executable(XLedger
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${XLEDGER_SOURCES}
    resources.qrc
    ${app_icon_resource_windows}
)

target_include_directories(XLedger PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/view
)


target_link_libraries(XLedger PRIVATE
    xledger_core
    xxun-ui
    
)

set_target_properties(XLedger PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# =========================================================
# 3. TEST
# =========================================================



if(BUILD_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()




# =========================================================
# 4. INSTALL
# =========================================================

include(GNUInstallDirs)
install(TARGETS XLedger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# 生成部署脚本
set(deploy_tool_options_arg  
    --no-compiler-runtime 
    --no-translations 
    --no-opengl-sw 
    --no-system-d3d-compiler
    --no-system-dxc-compiler
)
qt_generate_deploy_app_script(
    TARGET XLedger
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    EXCLUDE_PLUGIN_TYPES
        generic
        iconengines
        imageformats
        styles
    DEPLOY_TOOL_OPTIONS ${deploy_tool_options_arg}
)

install(SCRIPT ${deploy_script})