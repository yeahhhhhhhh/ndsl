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
CMAKE_SOURCE_DIR = /home/user/Desktop/ndsl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/ndsl/build

# Include any dependencies generated for this target.
include src/ndsl/CMakeFiles/ndsl.dir/depend.make

# Include the progress variables for this target.
include src/ndsl/CMakeFiles/ndsl.dir/progress.make

# Include the compile flags for this target's objects.
include src/ndsl/CMakeFiles/ndsl.dir/flags.make

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o: ../src/ndsl/net/BaseChannel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/BaseChannel.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/BaseChannel.cc

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/BaseChannel.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/BaseChannel.cc > CMakeFiles/ndsl.dir/net/BaseChannel.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/BaseChannel.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/BaseChannel.cc -o CMakeFiles/ndsl.dir/net/BaseChannel.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o: ../src/ndsl/net/TcpChannel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/TcpChannel.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/TcpChannel.cc

src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/TcpChannel.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/TcpChannel.cc > CMakeFiles/ndsl.dir/net/TcpChannel.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/TcpChannel.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/TcpChannel.cc -o CMakeFiles/ndsl.dir/net/TcpChannel.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o: ../src/ndsl/net/TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/TcpConnection.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/TcpConnection.cc

src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/TcpConnection.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/TcpConnection.cc > CMakeFiles/ndsl.dir/net/TcpConnection.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/TcpConnection.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/TcpConnection.cc -o CMakeFiles/ndsl.dir/net/TcpConnection.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o: ../src/ndsl/net/TcpAcceptor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/TcpAcceptor.cc

src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/TcpAcceptor.cc > CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/TcpAcceptor.cc -o CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o: ../src/ndsl/net/TcpClient.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/TcpClient.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/TcpClient.cc

src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/TcpClient.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/TcpClient.cc > CMakeFiles/ndsl.dir/net/TcpClient.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/TcpClient.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/TcpClient.cc -o CMakeFiles/ndsl.dir/net/TcpClient.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o: ../src/ndsl/net/SocketAddress.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/SocketAddress.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/SocketAddress.cc

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/SocketAddress.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/SocketAddress.cc > CMakeFiles/ndsl.dir/net/SocketAddress.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/SocketAddress.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/SocketAddress.cc -o CMakeFiles/ndsl.dir/net/SocketAddress.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o


src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o: ../src/ndsl/net/SocketAddressUn.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o -c /home/user/Desktop/ndsl/src/ndsl/net/SocketAddressUn.cc

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/net/SocketAddressUn.cc > CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.i

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/net/SocketAddressUn.cc -o CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.s

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o


src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o: ../src/ndsl/utils/Log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/utils/Log.cc.o -c /home/user/Desktop/ndsl/src/ndsl/utils/Log.cc

src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/utils/Log.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/utils/Log.cc > CMakeFiles/ndsl.dir/utils/Log.cc.i

src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/utils/Log.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/utils/Log.cc -o CMakeFiles/ndsl.dir/utils/Log.cc.s

src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o


src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o: ../src/ndsl/utils/TimeStamp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o -c /home/user/Desktop/ndsl/src/ndsl/utils/TimeStamp.cc

src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/utils/TimeStamp.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/utils/TimeStamp.cc > CMakeFiles/ndsl.dir/utils/TimeStamp.cc.i

src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/utils/TimeStamp.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/utils/TimeStamp.cc -o CMakeFiles/ndsl.dir/utils/TimeStamp.cc.s

src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o


src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o: ../src/ndsl/utils/Plugin.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/utils/Plugin.cc.o -c /home/user/Desktop/ndsl/src/ndsl/utils/Plugin.cc

src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/utils/Plugin.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/utils/Plugin.cc > CMakeFiles/ndsl.dir/utils/Plugin.cc.i

src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/utils/Plugin.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/utils/Plugin.cc -o CMakeFiles/ndsl.dir/utils/Plugin.cc.s

src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o


src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o: src/ndsl/CMakeFiles/ndsl.dir/flags.make
src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o: ../src/ndsl/utils/Guid.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ndsl.dir/utils/Guid.cc.o -c /home/user/Desktop/ndsl/src/ndsl/utils/Guid.cc

src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ndsl.dir/utils/Guid.cc.i"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Desktop/ndsl/src/ndsl/utils/Guid.cc > CMakeFiles/ndsl.dir/utils/Guid.cc.i

src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ndsl.dir/utils/Guid.cc.s"
	cd /home/user/Desktop/ndsl/build/src/ndsl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Desktop/ndsl/src/ndsl/utils/Guid.cc -o CMakeFiles/ndsl.dir/utils/Guid.cc.s

src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.requires:

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.requires

src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.provides: src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.requires
	$(MAKE) -f src/ndsl/CMakeFiles/ndsl.dir/build.make src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.provides.build
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.provides

src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.provides.build: src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o


# Object files for target ndsl
ndsl_OBJECTS = \
"CMakeFiles/ndsl.dir/net/BaseChannel.cc.o" \
"CMakeFiles/ndsl.dir/net/TcpChannel.cc.o" \
"CMakeFiles/ndsl.dir/net/TcpConnection.cc.o" \
"CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o" \
"CMakeFiles/ndsl.dir/net/TcpClient.cc.o" \
"CMakeFiles/ndsl.dir/net/SocketAddress.cc.o" \
"CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o" \
"CMakeFiles/ndsl.dir/utils/Log.cc.o" \
"CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o" \
"CMakeFiles/ndsl.dir/utils/Plugin.cc.o" \
"CMakeFiles/ndsl.dir/utils/Guid.cc.o"

# External object files for target ndsl
ndsl_EXTERNAL_OBJECTS =

bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/build.make
bin/libndsl.a: src/ndsl/CMakeFiles/ndsl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Desktop/ndsl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library ../../bin/libndsl.a"
	cd /home/user/Desktop/ndsl/build/src/ndsl && $(CMAKE_COMMAND) -P CMakeFiles/ndsl.dir/cmake_clean_target.cmake
	cd /home/user/Desktop/ndsl/build/src/ndsl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ndsl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ndsl/CMakeFiles/ndsl.dir/build: bin/libndsl.a

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/build

src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/BaseChannel.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/TcpChannel.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/TcpConnection.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/TcpAcceptor.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/TcpClient.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddress.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/net/SocketAddressUn.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/utils/Log.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/utils/TimeStamp.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/utils/Plugin.cc.o.requires
src/ndsl/CMakeFiles/ndsl.dir/requires: src/ndsl/CMakeFiles/ndsl.dir/utils/Guid.cc.o.requires

.PHONY : src/ndsl/CMakeFiles/ndsl.dir/requires

src/ndsl/CMakeFiles/ndsl.dir/clean:
	cd /home/user/Desktop/ndsl/build/src/ndsl && $(CMAKE_COMMAND) -P CMakeFiles/ndsl.dir/cmake_clean.cmake
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/clean

src/ndsl/CMakeFiles/ndsl.dir/depend:
	cd /home/user/Desktop/ndsl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Desktop/ndsl /home/user/Desktop/ndsl/src/ndsl /home/user/Desktop/ndsl/build /home/user/Desktop/ndsl/build/src/ndsl /home/user/Desktop/ndsl/build/src/ndsl/CMakeFiles/ndsl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ndsl/CMakeFiles/ndsl.dir/depend

