# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.7

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\projects\CPP\RawTools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\projects\CPP\RawTools\cmake-build

# Include any dependencies generated for this target.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/depend.make

# Include the progress variables for this target.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/progress.make

# Include the compile flags for this target's objects.
include RawToolsTest/CMakeFiles/RawToolsTest.dir/flags.make

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj: RawToolsTest/CMakeFiles/RawToolsTest.dir/flags.make
RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj: RawToolsTest/CMakeFiles/RawToolsTest.dir/includes_CXX.rsp
RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj: ../RawToolsTest/RawToolsTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\projects\CPP\RawTools\cmake-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj"
	cd /d E:\projects\CPP\RawTools\cmake-build\RawToolsTest && D:\TDM-GCC-64\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\RawToolsTest.dir\RawToolsTest.cpp.obj -c E:\projects\CPP\RawTools\RawToolsTest\RawToolsTest.cpp

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.i"
	cd /d E:\projects\CPP\RawTools\cmake-build\RawToolsTest && D:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\projects\CPP\RawTools\RawToolsTest\RawToolsTest.cpp > CMakeFiles\RawToolsTest.dir\RawToolsTest.cpp.i

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.s"
	cd /d E:\projects\CPP\RawTools\cmake-build\RawToolsTest && D:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\projects\CPP\RawTools\RawToolsTest\RawToolsTest.cpp -o CMakeFiles\RawToolsTest.dir\RawToolsTest.cpp.s

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.requires:

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.requires

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.provides: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.requires
	$(MAKE) -f RawToolsTest\CMakeFiles\RawToolsTest.dir\build.make RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.provides.build
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.provides

RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.provides.build: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj


# Object files for target RawToolsTest
RawToolsTest_OBJECTS = \
"CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj"

# External object files for target RawToolsTest
RawToolsTest_EXTERNAL_OBJECTS =

RawToolsTest/RawToolsTest.exe: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj
RawToolsTest/RawToolsTest.exe: RawToolsTest/CMakeFiles/RawToolsTest.dir/build.make
RawToolsTest/RawToolsTest.exe: RawToolsLib/libRawToolsLib.a
RawToolsTest/RawToolsTest.exe: RawToolsTest/CMakeFiles/RawToolsTest.dir/linklibs.rsp
RawToolsTest/RawToolsTest.exe: RawToolsTest/CMakeFiles/RawToolsTest.dir/objects1.rsp
RawToolsTest/RawToolsTest.exe: RawToolsTest/CMakeFiles/RawToolsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\projects\CPP\RawTools\cmake-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RawToolsTest.exe"
	cd /d E:\projects\CPP\RawTools\cmake-build\RawToolsTest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RawToolsTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
RawToolsTest/CMakeFiles/RawToolsTest.dir/build: RawToolsTest/RawToolsTest.exe

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/build

RawToolsTest/CMakeFiles/RawToolsTest.dir/requires: RawToolsTest/CMakeFiles/RawToolsTest.dir/RawToolsTest.cpp.obj.requires

.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/requires

RawToolsTest/CMakeFiles/RawToolsTest.dir/clean:
	cd /d E:\projects\CPP\RawTools\cmake-build\RawToolsTest && $(CMAKE_COMMAND) -P CMakeFiles\RawToolsTest.dir\cmake_clean.cmake
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/clean

RawToolsTest/CMakeFiles/RawToolsTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\projects\CPP\RawTools E:\projects\CPP\RawTools\RawToolsTest E:\projects\CPP\RawTools\cmake-build E:\projects\CPP\RawTools\cmake-build\RawToolsTest E:\projects\CPP\RawTools\cmake-build\RawToolsTest\CMakeFiles\RawToolsTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : RawToolsTest/CMakeFiles/RawToolsTest.dir/depend

