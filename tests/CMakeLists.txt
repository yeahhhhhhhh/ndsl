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
<<<<<<< HEAD

#utils/LogTest.cc
utils/TimeStampTest.cc
utils/PluginTest.cc
utils/GuidTest.cc
=======
#net/MultiplexerTest.cc

#utils/LogTest.cc
#utils/TimeStampTest.cc

#utils/PluginTest.cc
#utils/GuidTest.cc
#net/TcpConnectionTest.cc
#pass
#net/TcpAcceptorTest.cc

>>>>>>> master_1
#net/TcpConnectionTest.cc
#net/TcpAcceptorTest.cc
#net/EventLoopTest.cc
#net/SignalfdTest.cc

<<<<<<< HEAD
=======
# net/TcpConnectionTest.cc
# net/TcpAcceptorTest.cc
#net/EventLoopTest.cc
#net/EpollTest.cc
#net/SignalfdTest.cc

#utils/EventLoopThreadpoolTest.cc

>>>>>>> master_1
)

# 设置ping-pong单元测试的文件
#set(pingserver ping-pong/server.cc)
#set(pingclient ping-pong/nClient.cc)

include_directories(${CMAKE_SOURCE_DIR}/tests)

<<<<<<< HEAD
# net和utils下的测试文件
add_executable(utest ${TEST})
add_dependencies(utest ndsl)
target_link_libraries(utest ndsl pthread) #boost_system)
target_link_libraries(utest uuid)
=======
add_executable(utest ${TEST})
add_dependencies(utest ndsl)
target_link_libraries(utest ndsl pthread) # boost_system)

>>>>>>> master_1

#add_executable(server ${pingserver})
#add_dependencies(server ndsl)
#target_link_libraries(server ndsl)

# 生成pingpong测试客户端
<<<<<<< HEAD
#add_dependencies(client ndsl)
#target_link_libraries(client ndsl boost_system pthread)
=======
#add_executable(client ${pingclient})
#add_dependencies(client ndsl)
#target_link_libraries(client ndsl boost_system)
>>>>>>> master_1

#设置插件单元测试
set(SRC_list Plugintest/plugintest.cc) #宏定义
add_executable(plugin ${SRC_list})  #生成可执行文件
target_link_libraries(plugin dl)
target_link_libraries(plugin libplugin)
