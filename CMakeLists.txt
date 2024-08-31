cmake_minimum_required(VERSION 3.28)
project(Grid_test)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_subdirectory(test)
set(SOURCE_FILES Grid.h
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
add_executable(Grid_test main.cpp)


add_library(core ${SOURCE_FILES})
target_link_libraries(Grid_test ${CURSES_LIBRARIES})
target_link_libraries(Grid_test core)
