##
# @file CMakeLists.txt
# @brief
# tests目录下cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
# include_directories(${PROJECT_BINARY_DIR}/include)

# catch要求打开异常
#string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

add_subdirectory(utils)
add_subdirectory(net)
