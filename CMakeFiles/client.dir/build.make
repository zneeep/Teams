# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /snap/cmake/1288/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1288/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/src/client/main.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client/main.c.o: src/client/main.c
CMakeFiles/client.dir/src/client/main.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client.dir/src/client/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/client/main.c.o -MF CMakeFiles/client.dir/src/client/main.c.o.d -o CMakeFiles/client.dir/src/client/main.c.o -c /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/client/main.c

CMakeFiles/client.dir/src/client/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/client/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/client/main.c > CMakeFiles/client.dir/src/client/main.c.i

CMakeFiles/client.dir/src/client/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/client/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/client/main.c -o CMakeFiles/client.dir/src/client/main.c.s

CMakeFiles/client.dir/src/common/ip_port_validation.c.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/common/ip_port_validation.c.o: src/common/ip_port_validation.c
CMakeFiles/client.dir/src/common/ip_port_validation.c.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/client.dir/src/common/ip_port_validation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/src/common/ip_port_validation.c.o -MF CMakeFiles/client.dir/src/common/ip_port_validation.c.o.d -o CMakeFiles/client.dir/src/common/ip_port_validation.c.o -c /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/common/ip_port_validation.c

CMakeFiles/client.dir/src/common/ip_port_validation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client.dir/src/common/ip_port_validation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/common/ip_port_validation.c > CMakeFiles/client.dir/src/common/ip_port_validation.c.i

CMakeFiles/client.dir/src/common/ip_port_validation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client.dir/src/common/ip_port_validation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/src/common/ip_port_validation.c -o CMakeFiles/client.dir/src/common/ip_port_validation.c.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client/main.c.o" \
"CMakeFiles/client.dir/src/common/ip_port_validation.c.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

myteams_client: CMakeFiles/client.dir/src/client/main.c.o
myteams_client: CMakeFiles/client.dir/src/common/ip_port_validation.c.o
myteams_client: CMakeFiles/client.dir/build.make
myteams_client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable myteams_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: myteams_client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux /home/lucas/Projects/B-NWP-400-LYN-4-1-myteams-lucas.siraux/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend
