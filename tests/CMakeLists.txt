##
# @file CMakeLists.txt
# @brief
# tests目录下cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${CMAKE_SOURCE_DIR}/include)

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# 设置单元测试的文件
set(TEST 

testMain.cc


#pass
#net/TcpAcceptorTest.cc
#net/TcpConnectionTest.cc

#net/EventLoopTest.cc
#net/EpollTest.cc

)



# set(TEST test.cc
#    utils/TimeStampTest.cc utils/LogTest.cc utils/ThreadTest.cc
# utils/SemaphoreTest.cc utils/SpinlockTest.cc
#    net/EventfdTest.cc net/EpollTest.cc net/TaskQueueTest.cc net/ReactorTest.cc
# net/AddressTest.cc net/SocketTest.cc net/TimerTest.cc net/DnsTest.cc
# )
# set(CMAKE_CXX_FLAGS "/EHsc ${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_SOURCE_DIR}/tests)

add_executable(utest ${TEST})
add_dependencies(utest ndsl)
target_link_libraries(utest ndsl pthread boost_system)

# add_executable(tmpMain tmpMain.cc)
# add_dependencies(tmpMain ndsl)
# target_link_libraries(tmpMain ndsl)
