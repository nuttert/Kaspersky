# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Test/build

# Include any dependencies generated for this target.
include Runner/CMakeFiles/Runner.dir/depend.make

# Include the progress variables for this target.
include Runner/CMakeFiles/Runner.dir/progress.make

# Include the compile flags for this target's objects.
include Runner/CMakeFiles/Runner.dir/flags.make

Runner/CMakeFiles/Runner.dir/Runner.cpp.o: Runner/CMakeFiles/Runner.dir/flags.make
Runner/CMakeFiles/Runner.dir/Runner.cpp.o: ../Runner/Runner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Runner/CMakeFiles/Runner.dir/Runner.cpp.o"
	cd /Test/build/Runner && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Runner.dir/Runner.cpp.o -c /Test/Runner/Runner.cpp

Runner/CMakeFiles/Runner.dir/Runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Runner.dir/Runner.cpp.i"
	cd /Test/build/Runner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Test/Runner/Runner.cpp > CMakeFiles/Runner.dir/Runner.cpp.i

Runner/CMakeFiles/Runner.dir/Runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Runner.dir/Runner.cpp.s"
	cd /Test/build/Runner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Test/Runner/Runner.cpp -o CMakeFiles/Runner.dir/Runner.cpp.s

Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o: Runner/CMakeFiles/Runner.dir/flags.make
Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o: ../Runner/impl/RunnerImpl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o"
	cd /Test/build/Runner && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o -c /Test/Runner/impl/RunnerImpl.cpp

Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.i"
	cd /Test/build/Runner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Test/Runner/impl/RunnerImpl.cpp > CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.i

Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.s"
	cd /Test/build/Runner && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Test/Runner/impl/RunnerImpl.cpp -o CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.s

# Object files for target Runner
Runner_OBJECTS = \
"CMakeFiles/Runner.dir/Runner.cpp.o" \
"CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o"

# External object files for target Runner
Runner_EXTERNAL_OBJECTS =

Runner/libRunner.a: Runner/CMakeFiles/Runner.dir/Runner.cpp.o
Runner/libRunner.a: Runner/CMakeFiles/Runner.dir/impl/RunnerImpl.cpp.o
Runner/libRunner.a: Runner/CMakeFiles/Runner.dir/build.make
Runner/libRunner.a: Runner/CMakeFiles/Runner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libRunner.a"
	cd /Test/build/Runner && $(CMAKE_COMMAND) -P CMakeFiles/Runner.dir/cmake_clean_target.cmake
	cd /Test/build/Runner && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Runner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Runner/CMakeFiles/Runner.dir/build: Runner/libRunner.a

.PHONY : Runner/CMakeFiles/Runner.dir/build

Runner/CMakeFiles/Runner.dir/clean:
	cd /Test/build/Runner && $(CMAKE_COMMAND) -P CMakeFiles/Runner.dir/cmake_clean.cmake
.PHONY : Runner/CMakeFiles/Runner.dir/clean

Runner/CMakeFiles/Runner.dir/depend:
	cd /Test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Test /Test/Runner /Test/build /Test/build/Runner /Test/build/Runner/CMakeFiles/Runner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Runner/CMakeFiles/Runner.dir/depend

