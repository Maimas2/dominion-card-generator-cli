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
CMAKE_SOURCE_DIR = /home/alex/Documents/ban-in-c++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Documents/ban-in-c++

# Include any dependencies generated for this target.
include glfw/tests/CMakeFiles/tearing.dir/depend.make

# Include the progress variables for this target.
include glfw/tests/CMakeFiles/tearing.dir/progress.make

# Include the compile flags for this target's objects.
include glfw/tests/CMakeFiles/tearing.dir/flags.make

glfw/tests/CMakeFiles/tearing.dir/tearing.c.o: glfw/tests/CMakeFiles/tearing.dir/flags.make
glfw/tests/CMakeFiles/tearing.dir/tearing.c.o: glfw/tests/tearing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw/tests/CMakeFiles/tearing.dir/tearing.c.o"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tearing.dir/tearing.c.o   -c /home/alex/Documents/ban-in-c++/glfw/tests/tearing.c

glfw/tests/CMakeFiles/tearing.dir/tearing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/tearing.c.i"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Documents/ban-in-c++/glfw/tests/tearing.c > CMakeFiles/tearing.dir/tearing.c.i

glfw/tests/CMakeFiles/tearing.dir/tearing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/tearing.c.s"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Documents/ban-in-c++/glfw/tests/tearing.c -o CMakeFiles/tearing.dir/tearing.c.s

glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o: glfw/tests/CMakeFiles/tearing.dir/flags.make
glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o: glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.o   -c /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c

glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/__/deps/glad_gl.c.i"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c > CMakeFiles/tearing.dir/__/deps/glad_gl.c.i

glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/__/deps/glad_gl.c.s"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.s

# Object files for target tearing
tearing_OBJECTS = \
"CMakeFiles/tearing.dir/tearing.c.o" \
"CMakeFiles/tearing.dir/__/deps/glad_gl.c.o"

# External object files for target tearing
tearing_EXTERNAL_OBJECTS =

glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/tearing.c.o
glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o
glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/build.make
glfw/tests/tearing: glfw/src/libglfw3.a
glfw/tests/tearing: /usr/lib/x86_64-linux-gnu/libm.so
glfw/tests/tearing: /usr/lib/x86_64-linux-gnu/librt.so
glfw/tests/tearing: /usr/lib/x86_64-linux-gnu/libm.so
glfw/tests/tearing: /usr/lib/x86_64-linux-gnu/libX11.so
glfw/tests/tearing: glfw/tests/CMakeFiles/tearing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tearing"
	cd /home/alex/Documents/ban-in-c++/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tearing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw/tests/CMakeFiles/tearing.dir/build: glfw/tests/tearing

.PHONY : glfw/tests/CMakeFiles/tearing.dir/build

glfw/tests/CMakeFiles/tearing.dir/clean:
	cd /home/alex/Documents/ban-in-c++/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/tearing.dir/cmake_clean.cmake
.PHONY : glfw/tests/CMakeFiles/tearing.dir/clean

glfw/tests/CMakeFiles/tearing.dir/depend:
	cd /home/alex/Documents/ban-in-c++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Documents/ban-in-c++ /home/alex/Documents/ban-in-c++/glfw/tests /home/alex/Documents/ban-in-c++ /home/alex/Documents/ban-in-c++/glfw/tests /home/alex/Documents/ban-in-c++/glfw/tests/CMakeFiles/tearing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/tests/CMakeFiles/tearing.dir/depend

