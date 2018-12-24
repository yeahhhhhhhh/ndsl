# @file CMakeLists.txt
# @brief
# src/com目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#
include_directories(${PROJECT_SOURCE_DIR}/include/ndsl/utils)
link_directories(${PROJECT_SOURCE_DIR}/src/lib)

set(LIB_NDSL_GUID Guid.cc)

add_library(ndsl SHARED ${LIB_NDSL_GUID})
target_link_libraries(ndsl libuuid.so)

# set(LIB_NDSL_SRC Log.cc Reactor.cc Timer.cc Dns.cc)
# add_library(ndsl SHARED ${LIB_NDSL_SRC})
# target_link_libraries(ndsl pthread)
