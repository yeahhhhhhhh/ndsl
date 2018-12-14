##
# @file CMakeLists.txt
# @brief
# tests目录下cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${PROJECT_SOURCE_DIR}/include/ndsl/utils)
include_directories(${PROJECT_SOURCE_DIR}/include/ndsl/net)
include_directories(${CMAKE_SOURCE_DIR}/include)

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# 设置单元测试的文件
set(TEST SocketAddressTest.cc)

add_executable(utest2 ${TEST})

target_link_libraries(utest2 ndsl2)

# set(TEST test.cc
    utils/TimeStampTest.cc utils/LogTest.cc utils/ThreadTest.cc
# utils/SemaphoreTest.cc utils/SpinlockTest.cc
    net/EventfdTest.cc net/EpollTest.cc net/TaskQueueTest.cc net/ReactorTest.cc
# net/AddressTest.cc net/SocketTest.cc net/TimerTest.cc net/DnsTest.cc
# )

# add_executable(utest ${TEST})
# add_dependencies(utest ndsl)
# target_link_libraries(utest ndsl pthread)
