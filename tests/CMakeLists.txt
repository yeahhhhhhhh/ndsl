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

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# 设置单元测试的文件
set(TEST 
test.cc

# All files
#net/EpollTest.cc
#net/EventLoopTest.cc
# net/MultiplexerTest.cc

#net/PipeAndFifoTest.cc
#net/SignalfdTest.cc
#net/TcpAcceptorTest.cc
#net/TcpConnectionTest.cc
# net/TimeWheelTest.cc
#net/UdpEndpointTest.cc 
#net/UnixAndTcpSocketAddressTest.cc
#net/UnixConnectionTest.cc

#utils/EndianTest.cc
#utils/ErrorTest.cc
#utils/EventLoopThreadpoolTest.cc
#utils/GuidTest.cc
#utils/LogTest.cc
#utils/PluginTest.cc
utils/ThreadTest.cc
#utils/TimeStampTest.cc
#utils/XMLConfig_test.cc
)

# 设置ping-pong单元测试的文件
set(pingserver ping-pong/server.cc)
set(pingclient ping-pong/nClient.cc)
include_directories(${CMAKE_SOURCE_DIR}/tests)

# net和utils下的测试文件
add_executable(utest ${TEST})
add_dependencies(utest ndsl)
target_link_libraries(utest ndsl)
target_link_libraries(utest ndsl pthread) # boost_system)

# 生成pingpong测试 服务端
add_executable(server ${pingserver})
add_dependencies(server ndsl)
target_link_libraries(server ndsl)

# 生成pingpong测试 客户端
add_executable(client ${pingclient})
add_dependencies(client ndsl)
target_link_libraries(client ndsl boost_system pthread)

#设置插件单元测试
#set(SRC_list Plugintest/plugintest.cc) #宏定义
#add_executable(plugin ${SRC_list})  #生成可执行文件
#target_link_libraries(plugin dl)
#target_link_libraries(plugin libplugin)


#设置Relayserver测试文件
set(test_server Relayserver/server.cc)
set(test_client Relayserver/client.cc)
set(tcprelay Relayserver/tcprelay.cc)
include_directories(${CMAKE_SOURCE_DIR}/tests)

# 生成Relayserver测试 服务端
add_executable(test_server ${test_server})
add_dependencies(test_server ndsl)
target_link_libraries(test_server ndsl)

# 生成Relayclient测试 客户端
add_executable(test_client ${test_client})
add_dependencies(test_client ndsl)
target_link_libraries(test_client ndsl boost_system pthread)

# 生成Relayserver测试 中继服务器
add_executable(tcprelay ${tcprelay})
add_dependencies(tcprelay ndsl)
target_link_libraries(tcprelay ndsl)