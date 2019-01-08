##
# @file CMakeLists.txt
# @brief
# tests目录下cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com

# 头文件查找路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# catch要求打开异常
string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# 设置单元测试的文件
set(TEST net/SignalfdTest.cc utils/GuidTest.cc)


# 添加可执行文件
add_executable(utest ${TEST})
target_link_libraries(utest ndsl uuid)




