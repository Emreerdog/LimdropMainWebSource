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
include drogon/examples/CMakeFiles/websocket_test.dir/depend.make

# Include the progress variables for this target.
include drogon/examples/CMakeFiles/websocket_test.dir/progress.make

# Include the compile flags for this target's objects.
include drogon/examples/CMakeFiles/websocket_test.dir/flags.make

drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o: drogon/examples/CMakeFiles/websocket_test.dir/flags.make
drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o: ../drogon/examples/simple_example_test/WebSocketTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o"
	cd /home/erdog1/embeddPython/build/drogon/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o -c /home/erdog1/embeddPython/drogon/examples/simple_example_test/WebSocketTest.cc

drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.i"
	cd /home/erdog1/embeddPython/build/drogon/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erdog1/embeddPython/drogon/examples/simple_example_test/WebSocketTest.cc > CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.i

drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.s"
	cd /home/erdog1/embeddPython/build/drogon/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erdog1/embeddPython/drogon/examples/simple_example_test/WebSocketTest.cc -o CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.s

# Object files for target websocket_test
websocket_test_OBJECTS = \
"CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o"

# External object files for target websocket_test
websocket_test_EXTERNAL_OBJECTS =

drogon/examples/websocket_test: drogon/examples/CMakeFiles/websocket_test.dir/simple_example_test/WebSocketTest.cc.o
drogon/examples/websocket_test: drogon/examples/CMakeFiles/websocket_test.dir/build.make
drogon/examples/websocket_test: drogon/libdrogon.a
drogon/examples/websocket_test: drogon/trantor/libtrantor.a
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libssl.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libcrypto.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libjsoncpp.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libuuid.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libpq.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libz.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libssl.so
drogon/examples/websocket_test: /usr/lib/x86_64-linux-gnu/libcrypto.so
drogon/examples/websocket_test: drogon/examples/CMakeFiles/websocket_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erdog1/embeddPython/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable websocket_test"
	cd /home/erdog1/embeddPython/build/drogon/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/websocket_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drogon/examples/CMakeFiles/websocket_test.dir/build: drogon/examples/websocket_test

.PHONY : drogon/examples/CMakeFiles/websocket_test.dir/build

drogon/examples/CMakeFiles/websocket_test.dir/clean:
	cd /home/erdog1/embeddPython/build/drogon/examples && $(CMAKE_COMMAND) -P CMakeFiles/websocket_test.dir/cmake_clean.cmake
.PHONY : drogon/examples/CMakeFiles/websocket_test.dir/clean

drogon/examples/CMakeFiles/websocket_test.dir/depend:
	cd /home/erdog1/embeddPython/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erdog1/embeddPython /home/erdog1/embeddPython/drogon/examples /home/erdog1/embeddPython/build /home/erdog1/embeddPython/build/drogon/examples /home/erdog1/embeddPython/build/drogon/examples/CMakeFiles/websocket_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : drogon/examples/CMakeFiles/websocket_test.dir/depend

