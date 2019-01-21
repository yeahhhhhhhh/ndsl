##
# @file CMakeLists.txt
# @brief
# tests目录下cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${CMAKE_SOURCE_DIR}/include)
#add_subdirectory(entitytest)
add_subdirectory(easytest)

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})


# 设置单元测试的文件
set(TEST 
    test.cc 

    # All files
    # net/EpollTest.cc
    # net/EventLoopTest.cc
    #net/MultiplexerTest.cc

    # net/PipeAndFifoTest.cc
    # net/SignalfdTest.cc
    net/TcpAcceptorTest.cc
    net/TcpConnectionTest.cc

    # net/TimeWheelTest.cc
    # net/UdpEndpointTest.cc
    # net/UnixAndTcpSocketAddressTest.cc
    # net/UnixConnectionTest.cc
    #net/ELThreadpoolTest.cc
    # net/SockoptTest.cc
    # net/EventfdTest.cc

    # utils/EndianTest.cc
    # utils/ErrorTest.cc
    # utils/GuidTest.cc
    # utils/LogTest.cc
    # utils/PluginTest.cc
    # utils/SemaphoreTest.cc
    # utils/TimeStampTest.cc
    # utils/XmlTest.cc
)

# 设置ping-pong单元测试的文件
set(pingserver ping-pong/server.cc)
set(pingclient ping-pong/nClient.cc)
include_directories(${CMAKE_SOURCE_DIR}/tests)

# net和utils下的测试文件
add_executable(utest ${TEST})
add_dependencies(utest ndsl)
target_link_libraries(utest ndsl pthread)

# 生成pingpong测试 服务端
add_executable(server ${pingserver})
add_dependencies(server ndsl)
target_link_libraries(server ndsl)

# 生成pingpong测试 客户端
add_executable(client ${pingclient})
add_dependencies(client ndsl)
target_link_libraries(client ndsl pthread)
