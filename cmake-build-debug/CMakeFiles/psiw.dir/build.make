# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /snap/clion/261/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/261/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/psiw.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/psiw.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/psiw.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/psiw.dir/flags.make

CMakeFiles/psiw.dir/main.c.o: CMakeFiles/psiw.dir/flags.make
CMakeFiles/psiw.dir/main.c.o: /home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/main.c
CMakeFiles/psiw.dir/main.c.o: CMakeFiles/psiw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/psiw.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/psiw.dir/main.c.o -MF CMakeFiles/psiw.dir/main.c.o.d -o CMakeFiles/psiw.dir/main.c.o -c "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/main.c"

CMakeFiles/psiw.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/psiw.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/main.c" > CMakeFiles/psiw.dir/main.c.i

CMakeFiles/psiw.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/psiw.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/main.c" -o CMakeFiles/psiw.dir/main.c.s

# Object files for target psiw
psiw_OBJECTS = \
"CMakeFiles/psiw.dir/main.c.o"

# External object files for target psiw
psiw_EXTERNAL_OBJECTS =

psiw: CMakeFiles/psiw.dir/main.c.o
psiw: CMakeFiles/psiw.dir/build.make
psiw: CMakeFiles/psiw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable psiw"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/psiw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/psiw.dir/build: psiw
.PHONY : CMakeFiles/psiw.dir/build

CMakeFiles/psiw.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/psiw.dir/cmake_clean.cmake
.PHONY : CMakeFiles/psiw.dir/clean

CMakeFiles/psiw.dir/depend:
	cd "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing" "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing" "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug" "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug" "/home/michael/LinuxSystem&ConcuringProgrammingInC/C_Multiprocessing/cmake-build-debug/CMakeFiles/psiw.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/psiw.dir/depend

