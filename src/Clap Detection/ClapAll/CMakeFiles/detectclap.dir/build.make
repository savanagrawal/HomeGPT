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
include CMakeFiles/detectclap.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/detectclap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/detectclap.dir/flags.make

CMakeFiles/detectclap.dir/detectclap.cpp.o: CMakeFiles/detectclap.dir/flags.make
CMakeFiles/detectclap.dir/detectclap.cpp.o: detectclap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/detectclap.dir/detectclap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/detectclap.dir/detectclap.cpp.o -c "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectclap.cpp"

CMakeFiles/detectclap.dir/detectclap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/detectclap.dir/detectclap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectclap.cpp" > CMakeFiles/detectclap.dir/detectclap.cpp.i

CMakeFiles/detectclap.dir/detectclap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/detectclap.dir/detectclap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/detectclap.cpp" -o CMakeFiles/detectclap.dir/detectclap.cpp.s

# Object files for target detectclap
detectclap_OBJECTS = \
"CMakeFiles/detectclap.dir/detectclap.cpp.o"

# External object files for target detectclap
detectclap_EXTERNAL_OBJECTS =

detectclap: CMakeFiles/detectclap.dir/detectclap.cpp.o
detectclap: CMakeFiles/detectclap.dir/build.make
detectclap: /usr/local/lib/libportaudio.so
detectclap: CMakeFiles/detectclap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable detectclap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/detectclap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/detectclap.dir/build: detectclap

.PHONY : CMakeFiles/detectclap.dir/build

CMakeFiles/detectclap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/detectclap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/detectclap.dir/clean

CMakeFiles/detectclap.dir/depend:
	cd "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll" "/home/pi/Downloads/HomeGPT-Savan/Clap Detection/ClapAll/CMakeFiles/detectclap.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/detectclap.dir/depend

