# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/w/Desktop/Reconstruction/Mapper-InfiniTAM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build

# Include any dependencies generated for this target.
include InfiniTAM/Utils/CMakeFiles/Utils.dir/depend.make

# Include the progress variables for this target.
include InfiniTAM/Utils/CMakeFiles/Utils.dir/progress.make

# Include the compile flags for this target's objects.
include InfiniTAM/Utils/CMakeFiles/Utils.dir/flags.make

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o: InfiniTAM/Utils/CMakeFiles/Utils.dir/flags.make
InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o: ../InfiniTAM/Utils/FileUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/FileUtils.cpp.o -c /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/FileUtils.cpp

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/FileUtils.cpp.i"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/FileUtils.cpp > CMakeFiles/Utils.dir/FileUtils.cpp.i

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/FileUtils.cpp.s"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/FileUtils.cpp -o CMakeFiles/Utils.dir/FileUtils.cpp.s

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires:

.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides: InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires
	$(MAKE) -f InfiniTAM/Utils/CMakeFiles/Utils.dir/build.make InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides.build
.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides

InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.provides.build: InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o


InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o: InfiniTAM/Utils/CMakeFiles/Utils.dir/flags.make
InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o: ../InfiniTAM/Utils/ImageIOpfm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/ImageIOpfm.cpp.o -c /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/ImageIOpfm.cpp

InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/ImageIOpfm.cpp.i"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/ImageIOpfm.cpp > CMakeFiles/Utils.dir/ImageIOpfm.cpp.i

InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/ImageIOpfm.cpp.s"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils/ImageIOpfm.cpp -o CMakeFiles/Utils.dir/ImageIOpfm.cpp.s

InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.requires:

.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.requires

InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.provides: InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.requires
	$(MAKE) -f InfiniTAM/Utils/CMakeFiles/Utils.dir/build.make InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.provides.build
.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.provides

InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.provides.build: InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o


# Object files for target Utils
Utils_OBJECTS = \
"CMakeFiles/Utils.dir/FileUtils.cpp.o" \
"CMakeFiles/Utils.dir/ImageIOpfm.cpp.o"

# External object files for target Utils
Utils_EXTERNAL_OBJECTS =

InfiniTAM/Utils/libUtils.a: InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o
InfiniTAM/Utils/libUtils.a: InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o
InfiniTAM/Utils/libUtils.a: InfiniTAM/Utils/CMakeFiles/Utils.dir/build.make
InfiniTAM/Utils/libUtils.a: InfiniTAM/Utils/CMakeFiles/Utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libUtils.a"
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && $(CMAKE_COMMAND) -P CMakeFiles/Utils.dir/cmake_clean_target.cmake
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
InfiniTAM/Utils/CMakeFiles/Utils.dir/build: InfiniTAM/Utils/libUtils.a

.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/build

InfiniTAM/Utils/CMakeFiles/Utils.dir/requires: InfiniTAM/Utils/CMakeFiles/Utils.dir/FileUtils.cpp.o.requires
InfiniTAM/Utils/CMakeFiles/Utils.dir/requires: InfiniTAM/Utils/CMakeFiles/Utils.dir/ImageIOpfm.cpp.o.requires

.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/requires

InfiniTAM/Utils/CMakeFiles/Utils.dir/clean:
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils && $(CMAKE_COMMAND) -P CMakeFiles/Utils.dir/cmake_clean.cmake
.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/clean

InfiniTAM/Utils/CMakeFiles/Utils.dir/depend:
	cd /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/w/Desktop/Reconstruction/Mapper-InfiniTAM /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/InfiniTAM/Utils /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils /home/w/Desktop/Reconstruction/Mapper-InfiniTAM/build/InfiniTAM/Utils/CMakeFiles/Utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : InfiniTAM/Utils/CMakeFiles/Utils.dir/depend

