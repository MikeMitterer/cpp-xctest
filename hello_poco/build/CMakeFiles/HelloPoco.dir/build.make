# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.8.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.8.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build

# Include any dependencies generated for this target.
include CMakeFiles/HelloPoco.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloPoco.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloPoco.dir/flags.make

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o: CMakeFiles/HelloPoco.dir/flags.make
CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o: ../src/hello_poco.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o -c /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/src/hello_poco.cpp

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/src/hello_poco.cpp > CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.i

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/src/hello_poco.cpp -o CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.s

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.requires:

.PHONY : CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.requires

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.provides: CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.requires
	$(MAKE) -f CMakeFiles/HelloPoco.dir/build.make CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.provides.build
.PHONY : CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.provides

CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.provides.build: CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o


# Object files for target HelloPoco
HelloPoco_OBJECTS = \
"CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o"

# External object files for target HelloPoco
HelloPoco_EXTERNAL_OBJECTS =

../bin/mac/HelloPoco: CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o
../bin/mac/HelloPoco: CMakeFiles/HelloPoco.dir/build.make
../bin/mac/HelloPoco: /usr/local/lib/libPocoFoundation.dylib
../bin/mac/HelloPoco: /usr/local/lib/libPocoNet.dylib
../bin/mac/HelloPoco: /usr/local/lib/libPocoUtil.dylib
../bin/mac/HelloPoco: CMakeFiles/HelloPoco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/mac/HelloPoco"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloPoco.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloPoco.dir/build: ../bin/mac/HelloPoco

.PHONY : CMakeFiles/HelloPoco.dir/build

CMakeFiles/HelloPoco.dir/requires: CMakeFiles/HelloPoco.dir/src/hello_poco.cpp.o.requires

.PHONY : CMakeFiles/HelloPoco.dir/requires

CMakeFiles/HelloPoco.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloPoco.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloPoco.dir/clean

CMakeFiles/HelloPoco.dir/depend:
	cd /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build /Volumes/Daten/DevLocal/DevCPP/Projects/XCTest/hello_poco/build/CMakeFiles/HelloPoco.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloPoco.dir/depend

