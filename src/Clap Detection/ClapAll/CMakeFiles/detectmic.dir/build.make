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
CMAKE_SOURCE_DIR = "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll"

# Include any dependencies generated for this target.
include CMakeFiles/detectmic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/detectmic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/detectmic.dir/flags.make

CMakeFiles/detectmic.dir/detectmic.cpp.o: CMakeFiles/detectmic.dir/flags.make
CMakeFiles/detectmic.dir/detectmic.cpp.o: detectmic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/detectmic.dir/detectmic.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/detectmic.dir/detectmic.cpp.o -c "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectmic.cpp"

CMakeFiles/detectmic.dir/detectmic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/detectmic.dir/detectmic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectmic.cpp" > CMakeFiles/detectmic.dir/detectmic.cpp.i

CMakeFiles/detectmic.dir/detectmic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/detectmic.dir/detectmic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectmic.cpp" -o CMakeFiles/detectmic.dir/detectmic.cpp.s

# Object files for target detectmic
detectmic_OBJECTS = \
"CMakeFiles/detectmic.dir/detectmic.cpp.o"

# External object files for target detectmic
detectmic_EXTERNAL_OBJECTS =

detectmic: CMakeFiles/detectmic.dir/detectmic.cpp.o
detectmic: CMakeFiles/detectmic.dir/build.make
detectmic: /usr/local/lib/libportaudio.a
detectmic: CMakeFiles/detectmic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable detectmic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/detectmic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/detectmic.dir/build: detectmic

.PHONY : CMakeFiles/detectmic.dir/build

CMakeFiles/detectmic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/detectmic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/detectmic.dir/clean

CMakeFiles/detectmic.dir/depend:
	cd "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles/detectmic.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/detectmic.dir/depend

