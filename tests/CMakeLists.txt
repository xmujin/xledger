project(mytest LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test Core)
find_package(GTest CONFIG REQUIRED)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)



qt_add_executable(billmodeltest tst_billmodel.cpp)
qt_add_executable(addbillpresentertest tst_addbillpresenter.cpp)
qt_add_executable(addcategorytagpresentertest tst_addcategorytagpresenter.cpp)
target_include_directories(addbillpresentertest PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
)

target_include_directories(addcategorytagpresentertest PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
)


add_test(NAME billmodeltest COMMAND billmodeltest)
add_test(NAME addbillpresentertest COMMAND addbillpresentertest)
add_test(NAME addcategorytagpresentertest COMMAND addcategorytagpresentertest)

target_link_libraries(billmodeltest PRIVATE Qt6::Test Qt6::Core xledger_core GTest::gmock)
target_link_libraries(addbillpresentertest PRIVATE Qt6::Test Qt6::Core xledger_core GTest::gmock)
target_link_libraries(addcategorytagpresentertest PRIVATE Qt6::Test Qt6::Core xledger_core GTest::gmock)
