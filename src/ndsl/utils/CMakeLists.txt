# @file CMakeLists.txt
# @brief
# src/com目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${PROJECT_SOURCE_DIR}/include/ndsl/utils)
link_directories(${PROJECT_SOURCE_DIR}/src/lib)

set(LIB_NDSL_SRC Guid.cc)

add_library(ndsl SHARED ${LIB_NDSL_SRC})

#target_link_libraries(ndsl libuuid.a)
target_link_libraries(ndsl libuuid.so)

