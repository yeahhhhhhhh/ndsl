##
# @file CMakeLists.txt
# @brief
# src/com目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置需要编译的文件
set(LIB_NDSL_SRC Log.cc TimeStamp.cc main.cc)
add_library(ndsl SHARED ${LIB_NDSL_SRC})
add_executable(main ${LIB_NDSL_SRC})
target_link_libraries(ndsl pthread)
