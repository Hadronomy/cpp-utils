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
CMAKE_SOURCE_DIR = /home/hadronomy/repos/cpp-utils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hadronomy/repos/cpp-utils/build

# Include any dependencies generated for this target.
include CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/utils.dir/flags.make

CMakeFiles/utils.dir/src/cli/cli.cc.o: CMakeFiles/utils.dir/flags.make
CMakeFiles/utils.dir/src/cli/cli.cc.o: ../src/cli/cli.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadronomy/repos/cpp-utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/utils.dir/src/cli/cli.cc.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/src/cli/cli.cc.o -c /home/hadronomy/repos/cpp-utils/src/cli/cli.cc

CMakeFiles/utils.dir/src/cli/cli.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/src/cli/cli.cc.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadronomy/repos/cpp-utils/src/cli/cli.cc > CMakeFiles/utils.dir/src/cli/cli.cc.i

CMakeFiles/utils.dir/src/cli/cli.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/src/cli/cli.cc.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadronomy/repos/cpp-utils/src/cli/cli.cc -o CMakeFiles/utils.dir/src/cli/cli.cc.s

CMakeFiles/utils.dir/src/colors/colors.cc.o: CMakeFiles/utils.dir/flags.make
CMakeFiles/utils.dir/src/colors/colors.cc.o: ../src/colors/colors.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadronomy/repos/cpp-utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/utils.dir/src/colors/colors.cc.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/src/colors/colors.cc.o -c /home/hadronomy/repos/cpp-utils/src/colors/colors.cc

CMakeFiles/utils.dir/src/colors/colors.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/src/colors/colors.cc.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadronomy/repos/cpp-utils/src/colors/colors.cc > CMakeFiles/utils.dir/src/colors/colors.cc.i

CMakeFiles/utils.dir/src/colors/colors.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/src/colors/colors.cc.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadronomy/repos/cpp-utils/src/colors/colors.cc -o CMakeFiles/utils.dir/src/colors/colors.cc.s

CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o: CMakeFiles/utils.dir/flags.make
CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o: ../src/hourglass/hourglass.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadronomy/repos/cpp-utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o -c /home/hadronomy/repos/cpp-utils/src/hourglass/hourglass.cc

CMakeFiles/utils.dir/src/hourglass/hourglass.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/src/hourglass/hourglass.cc.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadronomy/repos/cpp-utils/src/hourglass/hourglass.cc > CMakeFiles/utils.dir/src/hourglass/hourglass.cc.i

CMakeFiles/utils.dir/src/hourglass/hourglass.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/src/hourglass/hourglass.cc.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadronomy/repos/cpp-utils/src/hourglass/hourglass.cc -o CMakeFiles/utils.dir/src/hourglass/hourglass.cc.s

CMakeFiles/utils.dir/src/misc/misc.cc.o: CMakeFiles/utils.dir/flags.make
CMakeFiles/utils.dir/src/misc/misc.cc.o: ../src/misc/misc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hadronomy/repos/cpp-utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/utils.dir/src/misc/misc.cc.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/src/misc/misc.cc.o -c /home/hadronomy/repos/cpp-utils/src/misc/misc.cc

CMakeFiles/utils.dir/src/misc/misc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/src/misc/misc.cc.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hadronomy/repos/cpp-utils/src/misc/misc.cc > CMakeFiles/utils.dir/src/misc/misc.cc.i

CMakeFiles/utils.dir/src/misc/misc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/src/misc/misc.cc.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hadronomy/repos/cpp-utils/src/misc/misc.cc -o CMakeFiles/utils.dir/src/misc/misc.cc.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/src/cli/cli.cc.o" \
"CMakeFiles/utils.dir/src/colors/colors.cc.o" \
"CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o" \
"CMakeFiles/utils.dir/src/misc/misc.cc.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

libutils.a: CMakeFiles/utils.dir/src/cli/cli.cc.o
libutils.a: CMakeFiles/utils.dir/src/colors/colors.cc.o
libutils.a: CMakeFiles/utils.dir/src/hourglass/hourglass.cc.o
libutils.a: CMakeFiles/utils.dir/src/misc/misc.cc.o
libutils.a: CMakeFiles/utils.dir/build.make
libutils.a: CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hadronomy/repos/cpp-utils/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libutils.a"
	$(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/utils.dir/build: libutils.a

.PHONY : CMakeFiles/utils.dir/build

CMakeFiles/utils.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : CMakeFiles/utils.dir/clean

CMakeFiles/utils.dir/depend:
	cd /home/hadronomy/repos/cpp-utils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hadronomy/repos/cpp-utils /home/hadronomy/repos/cpp-utils /home/hadronomy/repos/cpp-utils/build /home/hadronomy/repos/cpp-utils/build /home/hadronomy/repos/cpp-utils/build/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/utils.dir/depend

