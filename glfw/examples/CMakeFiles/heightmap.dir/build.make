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
include glfw/examples/CMakeFiles/heightmap.dir/depend.make

# Include the progress variables for this target.
include glfw/examples/CMakeFiles/heightmap.dir/progress.make

# Include the compile flags for this target's objects.
include glfw/examples/CMakeFiles/heightmap.dir/flags.make

glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.o: glfw/examples/CMakeFiles/heightmap.dir/flags.make
glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.o: glfw/examples/heightmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.o"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/heightmap.dir/heightmap.c.o   -c /home/alex/Documents/ban-in-c++/glfw/examples/heightmap.c

glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/heightmap.c.i"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Documents/ban-in-c++/glfw/examples/heightmap.c > CMakeFiles/heightmap.dir/heightmap.c.i

glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/heightmap.c.s"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Documents/ban-in-c++/glfw/examples/heightmap.c -o CMakeFiles/heightmap.dir/heightmap.c.s

glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o: glfw/examples/CMakeFiles/heightmap.dir/flags.make
glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o: glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o   -c /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c

glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/heightmap.dir/__/deps/glad_gl.c.i"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c > CMakeFiles/heightmap.dir/__/deps/glad_gl.c.i

glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/heightmap.dir/__/deps/glad_gl.c.s"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Documents/ban-in-c++/glfw/deps/glad_gl.c -o CMakeFiles/heightmap.dir/__/deps/glad_gl.c.s

# Object files for target heightmap
heightmap_OBJECTS = \
"CMakeFiles/heightmap.dir/heightmap.c.o" \
"CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o"

# External object files for target heightmap
heightmap_EXTERNAL_OBJECTS =

glfw/examples/heightmap: glfw/examples/CMakeFiles/heightmap.dir/heightmap.c.o
glfw/examples/heightmap: glfw/examples/CMakeFiles/heightmap.dir/__/deps/glad_gl.c.o
glfw/examples/heightmap: glfw/examples/CMakeFiles/heightmap.dir/build.make
glfw/examples/heightmap: glfw/src/libglfw3.a
glfw/examples/heightmap: /usr/lib/x86_64-linux-gnu/libm.so
glfw/examples/heightmap: /usr/lib/x86_64-linux-gnu/librt.so
glfw/examples/heightmap: /usr/lib/x86_64-linux-gnu/libm.so
glfw/examples/heightmap: /usr/lib/x86_64-linux-gnu/libX11.so
glfw/examples/heightmap: glfw/examples/CMakeFiles/heightmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Documents/ban-in-c++/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable heightmap"
	cd /home/alex/Documents/ban-in-c++/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heightmap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw/examples/CMakeFiles/heightmap.dir/build: glfw/examples/heightmap

.PHONY : glfw/examples/CMakeFiles/heightmap.dir/build

glfw/examples/CMakeFiles/heightmap.dir/clean:
	cd /home/alex/Documents/ban-in-c++/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/heightmap.dir/cmake_clean.cmake
.PHONY : glfw/examples/CMakeFiles/heightmap.dir/clean

glfw/examples/CMakeFiles/heightmap.dir/depend:
	cd /home/alex/Documents/ban-in-c++ && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Documents/ban-in-c++ /home/alex/Documents/ban-in-c++/glfw/examples /home/alex/Documents/ban-in-c++ /home/alex/Documents/ban-in-c++/glfw/examples /home/alex/Documents/ban-in-c++/glfw/examples/CMakeFiles/heightmap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/examples/CMakeFiles/heightmap.dir/depend

