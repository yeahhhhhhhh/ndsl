# @file CMakeLists.txt
# @brief
# src/com目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${PROJECT_SOURCE_DIR}/include/ndsl/net)

set(LIB_NDSL_SRC SocketAddress.cc)

add_library(ndsl2 SHARED ${LIB_NDSL_SRC})

#target_link_libraries(ndsl libuuid.a)

