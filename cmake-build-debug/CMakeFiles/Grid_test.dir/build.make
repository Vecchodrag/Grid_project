# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/291/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/291/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/edoardo/CLionProjects/Grid_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edoardo/CLionProjects/Grid_project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Grid_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Grid_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Grid_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Grid_test.dir/flags.make

CMakeFiles/Grid_test.dir/main.cpp.o: CMakeFiles/Grid_test.dir/flags.make
CMakeFiles/Grid_test.dir/main.cpp.o: /home/edoardo/CLionProjects/Grid_project/main.cpp
CMakeFiles/Grid_test.dir/main.cpp.o: CMakeFiles/Grid_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/edoardo/CLionProjects/Grid_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Grid_test.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Grid_test.dir/main.cpp.o -MF CMakeFiles/Grid_test.dir/main.cpp.o.d -o CMakeFiles/Grid_test.dir/main.cpp.o -c /home/edoardo/CLionProjects/Grid_project/main.cpp

CMakeFiles/Grid_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Grid_test.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/edoardo/CLionProjects/Grid_project/main.cpp > CMakeFiles/Grid_test.dir/main.cpp.i

CMakeFiles/Grid_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Grid_test.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/edoardo/CLionProjects/Grid_project/main.cpp -o CMakeFiles/Grid_test.dir/main.cpp.s

# Object files for target Grid_test
Grid_test_OBJECTS = \
"CMakeFiles/Grid_test.dir/main.cpp.o"

# External object files for target Grid_test
Grid_test_EXTERNAL_OBJECTS =

Grid_test: CMakeFiles/Grid_test.dir/main.cpp.o
Grid_test: CMakeFiles/Grid_test.dir/build.make
Grid_test: /usr/lib/x86_64-linux-gnu/libcurses.so
Grid_test: /usr/lib/x86_64-linux-gnu/libform.so
Grid_test: CMakeFiles/Grid_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/edoardo/CLionProjects/Grid_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Grid_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Grid_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Grid_test.dir/build: Grid_test
.PHONY : CMakeFiles/Grid_test.dir/build

CMakeFiles/Grid_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Grid_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Grid_test.dir/clean

CMakeFiles/Grid_test.dir/depend:
	cd /home/edoardo/CLionProjects/Grid_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edoardo/CLionProjects/Grid_project /home/edoardo/CLionProjects/Grid_project /home/edoardo/CLionProjects/Grid_project/cmake-build-debug /home/edoardo/CLionProjects/Grid_project/cmake-build-debug /home/edoardo/CLionProjects/Grid_project/cmake-build-debug/CMakeFiles/Grid_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Grid_test.dir/depend

