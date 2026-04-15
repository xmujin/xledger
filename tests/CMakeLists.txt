project(mytest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test Core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)



qt_add_executable(mytest tst_billmodel.cpp tst_dsb.cpp)
add_test(NAME mytest COMMAND mytest)

target_link_libraries(mytest PRIVATE Qt6::Test Qt6::Core)