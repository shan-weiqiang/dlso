# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/osboxes/playground/dlso/dlso

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/osboxes/playground/dlso/dlso/build

# Include any dependencies generated for this target.
include somelib/CMakeFiles/somelib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include somelib/CMakeFiles/somelib.dir/compiler_depend.make

# Include the progress variables for this target.
include somelib/CMakeFiles/somelib.dir/progress.make

# Include the compile flags for this target's objects.
include somelib/CMakeFiles/somelib.dir/flags.make

somelib/CMakeFiles/somelib.dir/somelib.cpp.o: somelib/CMakeFiles/somelib.dir/flags.make
somelib/CMakeFiles/somelib.dir/somelib.cpp.o: ../somelib/somelib.cpp
somelib/CMakeFiles/somelib.dir/somelib.cpp.o: somelib/CMakeFiles/somelib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osboxes/playground/dlso/dlso/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object somelib/CMakeFiles/somelib.dir/somelib.cpp.o"
	cd /home/osboxes/playground/dlso/dlso/build/somelib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT somelib/CMakeFiles/somelib.dir/somelib.cpp.o -MF CMakeFiles/somelib.dir/somelib.cpp.o.d -o CMakeFiles/somelib.dir/somelib.cpp.o -c /home/osboxes/playground/dlso/dlso/somelib/somelib.cpp

somelib/CMakeFiles/somelib.dir/somelib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/somelib.dir/somelib.cpp.i"
	cd /home/osboxes/playground/dlso/dlso/build/somelib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/osboxes/playground/dlso/dlso/somelib/somelib.cpp > CMakeFiles/somelib.dir/somelib.cpp.i

somelib/CMakeFiles/somelib.dir/somelib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/somelib.dir/somelib.cpp.s"
	cd /home/osboxes/playground/dlso/dlso/build/somelib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/osboxes/playground/dlso/dlso/somelib/somelib.cpp -o CMakeFiles/somelib.dir/somelib.cpp.s

# Object files for target somelib
somelib_OBJECTS = \
"CMakeFiles/somelib.dir/somelib.cpp.o"

# External object files for target somelib
somelib_EXTERNAL_OBJECTS =

somelib/libsomelib.so: somelib/CMakeFiles/somelib.dir/somelib.cpp.o
somelib/libsomelib.so: somelib/CMakeFiles/somelib.dir/build.make
somelib/libsomelib.so: somelib/CMakeFiles/somelib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/osboxes/playground/dlso/dlso/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libsomelib.so"
	cd /home/osboxes/playground/dlso/dlso/build/somelib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/somelib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
somelib/CMakeFiles/somelib.dir/build: somelib/libsomelib.so
.PHONY : somelib/CMakeFiles/somelib.dir/build

somelib/CMakeFiles/somelib.dir/clean:
	cd /home/osboxes/playground/dlso/dlso/build/somelib && $(CMAKE_COMMAND) -P CMakeFiles/somelib.dir/cmake_clean.cmake
.PHONY : somelib/CMakeFiles/somelib.dir/clean

somelib/CMakeFiles/somelib.dir/depend:
	cd /home/osboxes/playground/dlso/dlso/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osboxes/playground/dlso/dlso /home/osboxes/playground/dlso/dlso/somelib /home/osboxes/playground/dlso/dlso/build /home/osboxes/playground/dlso/dlso/build/somelib /home/osboxes/playground/dlso/dlso/build/somelib/CMakeFiles/somelib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : somelib/CMakeFiles/somelib.dir/depend
