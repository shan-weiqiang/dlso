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
include dlopen/independentso/CMakeFiles/indep.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dlopen/independentso/CMakeFiles/indep.dir/compiler_depend.make

# Include the progress variables for this target.
include dlopen/independentso/CMakeFiles/indep.dir/progress.make

# Include the compile flags for this target's objects.
include dlopen/independentso/CMakeFiles/indep.dir/flags.make

dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o: dlopen/independentso/CMakeFiles/indep.dir/flags.make
dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o: ../dlopen/independentso/inde.cpp
dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o: dlopen/independentso/CMakeFiles/indep.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osboxes/playground/dlso/dlso/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o -MF CMakeFiles/indep.dir/inde.cpp.o.d -o CMakeFiles/indep.dir/inde.cpp.o -c /home/osboxes/playground/dlso/dlso/dlopen/independentso/inde.cpp

dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/indep.dir/inde.cpp.i"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/osboxes/playground/dlso/dlso/dlopen/independentso/inde.cpp > CMakeFiles/indep.dir/inde.cpp.i

dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/indep.dir/inde.cpp.s"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/osboxes/playground/dlso/dlso/dlopen/independentso/inde.cpp -o CMakeFiles/indep.dir/inde.cpp.s

dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o: dlopen/independentso/CMakeFiles/indep.dir/flags.make
dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o: ../dlopen/greet/src/Greet.cpp
dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o: dlopen/independentso/CMakeFiles/indep.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osboxes/playground/dlso/dlso/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o -MF CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o.d -o CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o -c /home/osboxes/playground/dlso/dlso/dlopen/greet/src/Greet.cpp

dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/indep.dir/__/greet/src/Greet.cpp.i"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/osboxes/playground/dlso/dlso/dlopen/greet/src/Greet.cpp > CMakeFiles/indep.dir/__/greet/src/Greet.cpp.i

dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/indep.dir/__/greet/src/Greet.cpp.s"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/osboxes/playground/dlso/dlso/dlopen/greet/src/Greet.cpp -o CMakeFiles/indep.dir/__/greet/src/Greet.cpp.s

# Object files for target indep
indep_OBJECTS = \
"CMakeFiles/indep.dir/inde.cpp.o" \
"CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o"

# External object files for target indep
indep_EXTERNAL_OBJECTS =

dlopen/independentso/libindep.so: dlopen/independentso/CMakeFiles/indep.dir/inde.cpp.o
dlopen/independentso/libindep.so: dlopen/independentso/CMakeFiles/indep.dir/__/greet/src/Greet.cpp.o
dlopen/independentso/libindep.so: dlopen/independentso/CMakeFiles/indep.dir/build.make
dlopen/independentso/libindep.so: dlopen/independentso/CMakeFiles/indep.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/osboxes/playground/dlso/dlso/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libindep.so"
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/indep.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dlopen/independentso/CMakeFiles/indep.dir/build: dlopen/independentso/libindep.so
.PHONY : dlopen/independentso/CMakeFiles/indep.dir/build

dlopen/independentso/CMakeFiles/indep.dir/clean:
	cd /home/osboxes/playground/dlso/dlso/build/dlopen/independentso && $(CMAKE_COMMAND) -P CMakeFiles/indep.dir/cmake_clean.cmake
.PHONY : dlopen/independentso/CMakeFiles/indep.dir/clean

dlopen/independentso/CMakeFiles/indep.dir/depend:
	cd /home/osboxes/playground/dlso/dlso/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osboxes/playground/dlso/dlso /home/osboxes/playground/dlso/dlso/dlopen/independentso /home/osboxes/playground/dlso/dlso/build /home/osboxes/playground/dlso/dlso/build/dlopen/independentso /home/osboxes/playground/dlso/dlso/build/dlopen/independentso/CMakeFiles/indep.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dlopen/independentso/CMakeFiles/indep.dir/depend

