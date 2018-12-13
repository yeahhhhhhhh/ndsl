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
 net/EventLoop.cc  )
 #net/WorkQueue.cc 
 #net/InterruptChannel.cc)


add_library(ndsl ${LIB_NDSL_SRC})
