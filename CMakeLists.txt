cmake_minimum_required(VERSION 3.28)
project(Grid_test)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Grid_test main.cpp
        Grid.h
        cell.h
        Menu_option.h
        observer.h
        subject.h
        Menu_option.h
        info_menu.h
        cell.cpp
        Grid.cpp
        Menu_option.cpp
        info_menu.cpp)
target_link_libraries(Grid_test ${CURSES_LIBRARIES})
