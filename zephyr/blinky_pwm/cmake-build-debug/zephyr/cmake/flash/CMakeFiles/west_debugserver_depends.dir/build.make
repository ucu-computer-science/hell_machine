# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/fenix/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/fenix/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fenix/UCU_hell_machine/zephyr/blinky_pwm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug

# Utility rule file for west_debugserver_depends.

# Include the progress variables for this target.
include zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/progress.make

zephyr/cmake/flash/CMakeFiles/west_debugserver_depends: zephyr/zephyr.elf
zephyr/cmake/flash/CMakeFiles/west_debugserver_depends: zephyr/zephyr.elf
zephyr/cmake/flash/CMakeFiles/west_debugserver_depends: zephyr/zephyr.elf
	cd /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug/zephyr/cmake/flash && /home/fenix/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E echo 

west_debugserver_depends: zephyr/cmake/flash/CMakeFiles/west_debugserver_depends
west_debugserver_depends: zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/build.make

.PHONY : west_debugserver_depends

# Rule to build all files generated by this target.
zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/build: west_debugserver_depends

.PHONY : zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/build

zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/clean:
	cd /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug/zephyr/cmake/flash && $(CMAKE_COMMAND) -P CMakeFiles/west_debugserver_depends.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/clean

zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/depend:
	cd /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fenix/UCU_hell_machine/zephyr/blinky_pwm /home/fenix/zephyrproject/zephyr/cmake/flash /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug/zephyr/cmake/flash /home/fenix/UCU_hell_machine/zephyr/blinky_pwm/cmake-build-debug/zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/flash/CMakeFiles/west_debugserver_depends.dir/depend
