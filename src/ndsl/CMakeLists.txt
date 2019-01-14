##
# @file CMakeLists.txt
# @brief
# ndsl目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third)

add_subdirectory(net)
add_subdirectory(utils)

set(LIB_NDSL_SRC

  #all files
 net/BaseChannel.cc
 net/EventLoop.cc
 net/PipeChannel.cc
 # net/SignalHandler.cc
 # net/TcpAcceptor.cc
 # net/TcpConnection.cc
 # net/UdpClient.cc
 net/UnixChannel.cc
 # net/Multiplexer.cc
#  net/Protbload.pb.cc
 net/SocketAddress.cc
 # net/TcpChannel.cc
 # net/TimeWheel.cc
 # net/UdpEndpoint.cc
 net/UnixConnection.cc
 net/Epoll.cc
 net/PipeAndFifo.cc
 #  net/SignalChannel.cc
 net/SocketAddressUn.cc
 # net/TcpClient.cc
 # net/UdpChannel.cc
 net/UnixAcceptor.cc

#  third/pugixml.cpp

#  utils/Clientplugin.cc
 utils/Endian.cc
 # utils/EventLoopThreadpool.cc
 utils/Interrupter.cc
 # utils/Plugin.cc
 utils/TimeStamp.cc
 utils/Error.cc
 # utils/Guid.cc
 utils/Log.cc
 # utils/Thread.cc
#  utils/xmlconfig.cpp
net/SocketOpt.cc
net/EventfdChannel.cc
net/EventfdConnection.cc
 )

list(APPEND LIB_NDSL_SRC ${LIB_NDSL_SRC1})
add_library(ndsl ${LIB_NDSL_SRC})
target_link_libraries(ndsl uuid)


#生成libplugin.so
 #set(LIB_SRC utils/Plugin.cc)
 #set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)  

 #add_library(libplugin SHARED ${LIB_SRC})
 #set_target_properties(libplugin PROPERTIES OUTPUT_NAME "plugin")

 #set(CLIENT_SRC utils/Clientplugin.cc)
 #set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)  

 #add_library(clientplugin SHARED ${CLIENT_SRC})
 #set_target_properties(clientplugin PROPERTIES OUTPUT_NAME "clientplugin")
