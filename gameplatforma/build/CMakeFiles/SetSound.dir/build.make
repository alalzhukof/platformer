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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alekseizhukov/Desktop/gameplatforma

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alekseizhukov/Desktop/gameplatforma/build

# Include any dependencies generated for this target.
include CMakeFiles/SetSound.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SetSound.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SetSound.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SetSound.dir/flags.make

CMakeFiles/SetSound.dir/setsound.cpp.o: CMakeFiles/SetSound.dir/flags.make
CMakeFiles/SetSound.dir/setsound.cpp.o: /Users/alekseizhukov/Desktop/gameplatforma/setsound.cpp
CMakeFiles/SetSound.dir/setsound.cpp.o: CMakeFiles/SetSound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alekseizhukov/Desktop/gameplatforma/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SetSound.dir/setsound.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SetSound.dir/setsound.cpp.o -MF CMakeFiles/SetSound.dir/setsound.cpp.o.d -o CMakeFiles/SetSound.dir/setsound.cpp.o -c /Users/alekseizhukov/Desktop/gameplatforma/setsound.cpp

CMakeFiles/SetSound.dir/setsound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SetSound.dir/setsound.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alekseizhukov/Desktop/gameplatforma/setsound.cpp > CMakeFiles/SetSound.dir/setsound.cpp.i

CMakeFiles/SetSound.dir/setsound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SetSound.dir/setsound.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alekseizhukov/Desktop/gameplatforma/setsound.cpp -o CMakeFiles/SetSound.dir/setsound.cpp.s

CMakeFiles/SetSound.dir/test3.cpp.o: CMakeFiles/SetSound.dir/flags.make
CMakeFiles/SetSound.dir/test3.cpp.o: /Users/alekseizhukov/Desktop/gameplatforma/test3.cpp
CMakeFiles/SetSound.dir/test3.cpp.o: CMakeFiles/SetSound.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alekseizhukov/Desktop/gameplatforma/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SetSound.dir/test3.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SetSound.dir/test3.cpp.o -MF CMakeFiles/SetSound.dir/test3.cpp.o.d -o CMakeFiles/SetSound.dir/test3.cpp.o -c /Users/alekseizhukov/Desktop/gameplatforma/test3.cpp

CMakeFiles/SetSound.dir/test3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SetSound.dir/test3.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alekseizhukov/Desktop/gameplatforma/test3.cpp > CMakeFiles/SetSound.dir/test3.cpp.i

CMakeFiles/SetSound.dir/test3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SetSound.dir/test3.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alekseizhukov/Desktop/gameplatforma/test3.cpp -o CMakeFiles/SetSound.dir/test3.cpp.s

# Object files for target SetSound
SetSound_OBJECTS = \
"CMakeFiles/SetSound.dir/setsound.cpp.o" \
"CMakeFiles/SetSound.dir/test3.cpp.o"

# External object files for target SetSound
SetSound_EXTERNAL_OBJECTS =

SetSound: CMakeFiles/SetSound.dir/setsound.cpp.o
SetSound: CMakeFiles/SetSound.dir/test3.cpp.o
SetSound: CMakeFiles/SetSound.dir/build.make
SetSound: CMakeFiles/SetSound.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/alekseizhukov/Desktop/gameplatforma/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SetSound"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SetSound.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SetSound.dir/build: SetSound
.PHONY : CMakeFiles/SetSound.dir/build

CMakeFiles/SetSound.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SetSound.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SetSound.dir/clean

CMakeFiles/SetSound.dir/depend:
	cd /Users/alekseizhukov/Desktop/gameplatforma/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alekseizhukov/Desktop/gameplatforma /Users/alekseizhukov/Desktop/gameplatforma /Users/alekseizhukov/Desktop/gameplatforma/build /Users/alekseizhukov/Desktop/gameplatforma/build /Users/alekseizhukov/Desktop/gameplatforma/build/CMakeFiles/SetSound.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SetSound.dir/depend

