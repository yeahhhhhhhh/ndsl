##
# @file CMakeLists.txt
# @brief
# ndsl目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
add_subdirectory(net)
add_subdirectory(utils)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIB_NDSL_SRC
 net/Epoll.cc
 net/EventLoop.cc
 net/BaseChannel.cc
 net/TcpChannel.cc
 net/TcpConnection.cc
 net/TcpAcceptor.cc
 net/SocketAddress.cc
 net/SocketAddressUn.cc
 net/TcpClient.cc
 net/SocketAddress.cc
 net/SocketAddressUn.cc
 utils/Log.cc
 utils/TimeStamp.cc
 utils/Plugin.cc
 utils/Guid.cc
 #net/WorkQueue.cc
 #net/InterruptChannel.cc
 net/SignalChannel.cc
 net/SignalHandler.cc
 )


add_library(ndsl ${LIB_NDSL_SRC})


