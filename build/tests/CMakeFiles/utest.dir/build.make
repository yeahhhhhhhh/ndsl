# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/ranxiangjun/ndsl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ranxiangjun/ndsl/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/utest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/utest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/utest.dir/flags.make

tests/CMakeFiles/utest.dir/testMain.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/testMain.cc.o: ../tests/testMain.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/utest.dir/testMain.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/testMain.cc.o -c /home/ranxiangjun/ndsl/tests/testMain.cc

tests/CMakeFiles/utest.dir/testMain.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/testMain.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/testMain.cc > CMakeFiles/utest.dir/testMain.cc.i

tests/CMakeFiles/utest.dir/testMain.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/testMain.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/testMain.cc -o CMakeFiles/utest.dir/testMain.cc.s

tests/CMakeFiles/utest.dir/testMain.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/testMain.cc.o.requires

tests/CMakeFiles/utest.dir/testMain.cc.o.provides: tests/CMakeFiles/utest.dir/testMain.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/testMain.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/testMain.cc.o.provides

tests/CMakeFiles/utest.dir/testMain.cc.o.provides.build: tests/CMakeFiles/utest.dir/testMain.cc.o


tests/CMakeFiles/utest.dir/utils/LogTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/utils/LogTest.cc.o: ../tests/utils/LogTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/utest.dir/utils/LogTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/utils/LogTest.cc.o -c /home/ranxiangjun/ndsl/tests/utils/LogTest.cc

tests/CMakeFiles/utest.dir/utils/LogTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/utils/LogTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/utils/LogTest.cc > CMakeFiles/utest.dir/utils/LogTest.cc.i

tests/CMakeFiles/utest.dir/utils/LogTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/utils/LogTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/utils/LogTest.cc -o CMakeFiles/utest.dir/utils/LogTest.cc.s

tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.requires

tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.provides: tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.provides

tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/utils/LogTest.cc.o


tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o: ../tests/utils/TimeStampTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/utils/TimeStampTest.cc.o -c /home/ranxiangjun/ndsl/tests/utils/TimeStampTest.cc

tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/utils/TimeStampTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/utils/TimeStampTest.cc > CMakeFiles/utest.dir/utils/TimeStampTest.cc.i

tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/utils/TimeStampTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/utils/TimeStampTest.cc -o CMakeFiles/utest.dir/utils/TimeStampTest.cc.s

tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.requires

tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.provides: tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.provides

tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o


tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o: ../tests/utils/PluginTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/utils/PluginTest.cc.o -c /home/ranxiangjun/ndsl/tests/utils/PluginTest.cc

tests/CMakeFiles/utest.dir/utils/PluginTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/utils/PluginTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/utils/PluginTest.cc > CMakeFiles/utest.dir/utils/PluginTest.cc.i

tests/CMakeFiles/utest.dir/utils/PluginTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/utils/PluginTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/utils/PluginTest.cc -o CMakeFiles/utest.dir/utils/PluginTest.cc.s

tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.requires

tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.provides: tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.provides

tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o


tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o: ../tests/utils/GuidTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/utils/GuidTest.cc.o -c /home/ranxiangjun/ndsl/tests/utils/GuidTest.cc

tests/CMakeFiles/utest.dir/utils/GuidTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/utils/GuidTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/utils/GuidTest.cc > CMakeFiles/utest.dir/utils/GuidTest.cc.i

tests/CMakeFiles/utest.dir/utils/GuidTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/utils/GuidTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/utils/GuidTest.cc -o CMakeFiles/utest.dir/utils/GuidTest.cc.s

tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.requires

tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.provides: tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.provides

tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o


tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o: ../tests/net/PipeAndFifoTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o -c /home/ranxiangjun/ndsl/tests/net/PipeAndFifoTest.cc

tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/net/PipeAndFifoTest.cc > CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.i

tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/net/PipeAndFifoTest.cc -o CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.s

tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.requires

tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.provides: tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.provides

tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o


tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o: ../tests/net/UnixAndTcpSocketAddressTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o -c /home/ranxiangjun/ndsl/tests/net/UnixAndTcpSocketAddressTest.cc

tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/net/UnixAndTcpSocketAddressTest.cc > CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.i

tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/net/UnixAndTcpSocketAddressTest.cc -o CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.s

tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.requires

tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.provides: tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.provides

tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o


tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o: tests/CMakeFiles/utest.dir/flags.make
tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o: ../tests/net/UnixConnectionTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o -c /home/ranxiangjun/ndsl/tests/net/UnixConnectionTest.cc

tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utest.dir/net/UnixConnectionTest.cc.i"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranxiangjun/ndsl/tests/net/UnixConnectionTest.cc > CMakeFiles/utest.dir/net/UnixConnectionTest.cc.i

tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utest.dir/net/UnixConnectionTest.cc.s"
	cd /home/ranxiangjun/ndsl/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranxiangjun/ndsl/tests/net/UnixConnectionTest.cc -o CMakeFiles/utest.dir/net/UnixConnectionTest.cc.s

tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.requires:

.PHONY : tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.requires

tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.provides: tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.requires
	$(MAKE) -f tests/CMakeFiles/utest.dir/build.make tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.provides.build
.PHONY : tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.provides

tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.provides.build: tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o


# Object files for target utest
utest_OBJECTS = \
"CMakeFiles/utest.dir/testMain.cc.o" \
"CMakeFiles/utest.dir/utils/LogTest.cc.o" \
"CMakeFiles/utest.dir/utils/TimeStampTest.cc.o" \
"CMakeFiles/utest.dir/utils/PluginTest.cc.o" \
"CMakeFiles/utest.dir/utils/GuidTest.cc.o" \
"CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o" \
"CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o" \
"CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o"

# External object files for target utest
utest_EXTERNAL_OBJECTS =

bin/utest: tests/CMakeFiles/utest.dir/testMain.cc.o
bin/utest: tests/CMakeFiles/utest.dir/utils/LogTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o
bin/utest: tests/CMakeFiles/utest.dir/build.make
bin/utest: bin/libndsl.a
bin/utest: tests/CMakeFiles/utest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ranxiangjun/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ../bin/utest"
	cd /home/ranxiangjun/ndsl/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/utest.dir/build: bin/utest

.PHONY : tests/CMakeFiles/utest.dir/build

tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/testMain.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/utils/LogTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/utils/TimeStampTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/utils/PluginTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/utils/GuidTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/net/PipeAndFifoTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/net/UnixAndTcpSocketAddressTest.cc.o.requires
tests/CMakeFiles/utest.dir/requires: tests/CMakeFiles/utest.dir/net/UnixConnectionTest.cc.o.requires

.PHONY : tests/CMakeFiles/utest.dir/requires

tests/CMakeFiles/utest.dir/clean:
	cd /home/ranxiangjun/ndsl/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/utest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/utest.dir/clean

tests/CMakeFiles/utest.dir/depend:
	cd /home/ranxiangjun/ndsl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ranxiangjun/ndsl /home/ranxiangjun/ndsl/tests /home/ranxiangjun/ndsl/build /home/ranxiangjun/ndsl/build/tests /home/ranxiangjun/ndsl/build/tests/CMakeFiles/utest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/utest.dir/depend

