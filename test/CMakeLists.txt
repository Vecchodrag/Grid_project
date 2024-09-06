cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 11)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp
        GridFixture.cpp
        CellFixture.cpp
        Menu_optionFixture.cpp
        info_menuFixture.cpp)
add_executable(runGridTests ${TEST_SOURCE_FILES})
target_link_libraries(runGridTests gtest gtest_main core ${CURSES_LIBRARIES})