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
CMAKE_SOURCE_DIR = /home/erdog1/embeddPython

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erdog1/embeddPython/build

# Include any dependencies generated for this target.
include drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/depend.make

# Include the progress variables for this target.
include drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/progress.make

# Include the compile flags for this target's objects.
include drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/flags.make

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.o: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/flags.make
drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.o: ../drogon/drogon_ctl/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.o"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_drogon_ctl.dir/main.cc.o -c /home/erdog1/embeddPython/drogon/drogon_ctl/main.cc

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_drogon_ctl.dir/main.cc.i"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erdog1/embeddPython/drogon/drogon_ctl/main.cc > CMakeFiles/_drogon_ctl.dir/main.cc.i

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_drogon_ctl.dir/main.cc.s"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erdog1/embeddPython/drogon/drogon_ctl/main.cc -o CMakeFiles/_drogon_ctl.dir/main.cc.s

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.o: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/flags.make
drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.o: ../drogon/drogon_ctl/cmd.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.o"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_drogon_ctl.dir/cmd.cc.o -c /home/erdog1/embeddPython/drogon/drogon_ctl/cmd.cc

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_drogon_ctl.dir/cmd.cc.i"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erdog1/embeddPython/drogon/drogon_ctl/cmd.cc > CMakeFiles/_drogon_ctl.dir/cmd.cc.i

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_drogon_ctl.dir/cmd.cc.s"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erdog1/embeddPython/drogon/drogon_ctl/cmd.cc -o CMakeFiles/_drogon_ctl.dir/cmd.cc.s

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.o: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/flags.make
drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.o: ../drogon/drogon_ctl/create.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.o"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_drogon_ctl.dir/create.cc.o -c /home/erdog1/embeddPython/drogon/drogon_ctl/create.cc

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_drogon_ctl.dir/create.cc.i"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erdog1/embeddPython/drogon/drogon_ctl/create.cc > CMakeFiles/_drogon_ctl.dir/create.cc.i

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_drogon_ctl.dir/create.cc.s"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erdog1/embeddPython/drogon/drogon_ctl/create.cc -o CMakeFiles/_drogon_ctl.dir/create.cc.s

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.o: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/flags.make
drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.o: ../drogon/drogon_ctl/create_view.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.o"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_drogon_ctl.dir/create_view.cc.o -c /home/erdog1/embeddPython/drogon/drogon_ctl/create_view.cc

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_drogon_ctl.dir/create_view.cc.i"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erdog1/embeddPython/drogon/drogon_ctl/create_view.cc > CMakeFiles/_drogon_ctl.dir/create_view.cc.i

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_drogon_ctl.dir/create_view.cc.s"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erdog1/embeddPython/drogon/drogon_ctl/create_view.cc -o CMakeFiles/_drogon_ctl.dir/create_view.cc.s

# Object files for target _drogon_ctl
_drogon_ctl_OBJECTS = \
"CMakeFiles/_drogon_ctl.dir/main.cc.o" \
"CMakeFiles/_drogon_ctl.dir/cmd.cc.o" \
"CMakeFiles/_drogon_ctl.dir/create.cc.o" \
"CMakeFiles/_drogon_ctl.dir/create_view.cc.o"

# External object files for target _drogon_ctl
_drogon_ctl_EXTERNAL_OBJECTS =

drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/main.cc.o
drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/cmd.cc.o
drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create.cc.o
drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/create_view.cc.o
drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/build.make
drogon/drogon_ctl/_drogon_ctl: drogon/libdrogon.a
drogon/drogon_ctl/_drogon_ctl: drogon/trantor/libtrantor.a
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libssl.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libcrypto.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libjsoncpp.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libuuid.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libpq.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libz.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libssl.so
drogon/drogon_ctl/_drogon_ctl: /usr/lib/x86_64-linux-gnu/libcrypto.so
drogon/drogon_ctl/_drogon_ctl: drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable _drogon_ctl"
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_drogon_ctl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/build: drogon/drogon_ctl/_drogon_ctl

.PHONY : drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/build

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/clean:
	cd /home/erdog1/embeddPython/build/drogon/drogon_ctl && $(CMAKE_COMMAND) -P CMakeFiles/_drogon_ctl.dir/cmake_clean.cmake
.PHONY : drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/clean

drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/depend:
	cd /home/erdog1/embeddPython/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erdog1/embeddPython /home/erdog1/embeddPython/drogon/drogon_ctl /home/erdog1/embeddPython/build /home/erdog1/embeddPython/build/drogon/drogon_ctl /home/erdog1/embeddPython/build/drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : drogon/drogon_ctl/CMakeFiles/_drogon_ctl.dir/depend

