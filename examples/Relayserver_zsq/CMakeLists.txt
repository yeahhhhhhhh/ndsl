##
# @file CMakeLists.txt
# @brief
# 中继服务器Cmake文件
#
# @author zsq
# @email 1575033031@qq.com
#

include_directories(${CMAKE_SOURCE_DIR}/include)


#设置Relayserver测试文件
set(test_server server.cc)
set(test_client client.cc)
set(tcprelay tcprelay.cc)
#include_directories(${CMAKE_SOURCE_DIR}/tests)

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