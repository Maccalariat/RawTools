# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/hans/projects/cpp/RawTools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hans/projects/cpp/RawTools/build

# Include any dependencies generated for this target.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/depend.make

# Include the progress variables for this target.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/progress.make

# Include the compile flags for this target's objects.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/flags.make

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o: RawToolsTest/CMakeFiles/RawToolsTest.dir/flags.make
RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o: ../RawToolsTest/RawToolsTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/projects/cpp/RawTools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o"
	cd /home/hans/projects/cpp/RawTools/build/RawToolsTest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o -c /home/hans/projects/cpp/RawTools/RawToolsTest/RawToolsTest.cpp

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.i"
	cd /home/hans/projects/cpp/RawTools/build/RawToolsTest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/projects/cpp/RawTools/RawToolsTest/RawToolsTest.cpp > CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.i

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.s"
	cd /home/hans/projects/cpp/RawTools/build/RawToolsTest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/projects/cpp/RawTools/RawToolsTest/RawToolsTest.cpp -o CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.s

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.requires:

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.requires

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.provides: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.requires
	$(MAKE) -f RawToolsTest/CMakeFiles/RawToolsTest.dir/build.make RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.provides.build
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.provides

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.provides.build: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o


# Object files for target RawToolsTest
RawToolsTest_OBJECTS = \
"CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o"

# External object files for target RawToolsTest
RawToolsTest_EXTERNAL_OBJECTS =

RawToolsTest/RawToolsTest: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o
RawToolsTest/RawToolsTest: RawToolsTest/CMakeFiles/RawToolsTest.dir/build.make
RawToolsTest/RawToolsTest: RawToolsLib/libRawToolsLib.a
RawToolsTest/RawToolsTest: RawToolsTest/CMakeFiles/RawToolsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hans/projects/cpp/RawTools/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RawToolsTest"
	cd /home/hans/projects/cpp/RawTools/build/RawToolsTest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RawToolsTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
RawToolsTest/CMakeFiles/RawToolsTest.dir/build: RawToolsTest/RawToolsTest

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/build

RawToolsTest/CMakeFiles/RawToolsTest.dir/requires: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.o.requires

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/requires

RawToolsTest/CMakeFiles/RawToolsTest.dir/clean:
	cd /home/hans/projects/cpp/RawTools/build/RawToolsTest && $(CMAKE_COMMAND) -P CMakeFiles/RawToolsTest.dir/cmake_clean.cmake
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/clean

RawToolsTest/CMakeFiles/RawToolsTest.dir/depend:
	cd /home/hans/projects/cpp/RawTools/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hans/projects/cpp/RawTools /home/hans/projects/cpp/RawTools/RawToolsTest /home/hans/projects/cpp/RawTools/build /home/hans/projects/cpp/RawTools/build/RawToolsTest /home/hans/projects/cpp/RawTools/build/RawToolsTest/CMakeFiles/RawToolsTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/depend

