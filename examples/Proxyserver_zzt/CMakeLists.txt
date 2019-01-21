##
# @file CMakeLists.txt
# @brief 
#
# @author zzt
# @emial 429834658@qq.com
##

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
   message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found\n")
endif()
include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS Protbload.proto)

# 生成client客户端程序
set(SRC_CLIENT Client.cc)
ADD_EXECUTABLE(client ${SRC_CLIENT} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(client ndsl)
target_link_libraries(client ndsl pthread protobuf ${PROTOBUF_LIBRARIES})

# 生成server服务端程序
set(SRC_SERVER Server.cc)
ADD_EXECUTABLE(server ${SRC_SERVER} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(server ndsl)
target_link_libraries(server ndsl pthread protobuf ${PROTOBUF_LIBRARIES})