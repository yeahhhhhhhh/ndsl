##
# @file CMakeLists.txt
# @brief
# ndsl目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIB_NDSL_SRC
 net/Epoll.cc
 net/EventLoop.cc
 net/BaseChannel.cc
 #net/TcpChannel.cc
 #net/TcpConnection.cc
 #net/TcpAcceptor.cc
 #net/TcpClient.cc

 #net/SocketAddress.cc
 #net/SocketAddressUn.cc

 #net/SocketAddress.cc
 #net/SocketAddressUn.cc
 utils/Log.cc
 utils/TimeStamp.cc
 #net/WorkQueue.cc
 #net/InterruptChannel.cc
 net/SignalChannel.cc
 net/SignalHandler.cc
 
 utils/Guid.cc
 )

add_library(ndsl ${LIB_NDSL_SRC})
target_link_libraries(ndsl uuid)

