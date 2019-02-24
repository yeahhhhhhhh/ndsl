##
# @file CMakeLists.txt
# @brief
# ftpserver Cmake文件
#
# @author lanry
# @email luckylanry@163.com
#

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

# 生成FtpClient客户端程序
set(SRC_CLIENT FtpClient_.cc)
ADD_EXECUTABLE(ftpclient ${SRC_CLIENT} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(ftpclient ndsl)
target_link_libraries(ftpclient ndsl pthread protobuf ${PROTOBUF_LIBRARIES})

# 生成FtpServer服务端程序
set(SRC_SERVER FtpServer_.cc)
ADD_EXECUTABLE(ftpserver ${SRC_SERVER} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(ftpserver ndsl)
target_link_libraries(ftpserver ndsl pthread protobuf ${PROTOBUF_LIBRARIES})

set(SRC_FTPCLIENT  FtpClientHandle.cc FtpClient.cc)
ADD_EXECUTABLE(client ${SRC_FTPCLIENT} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(client ndsl)
target_link_libraries(client ndsl pthread protobuf ${PROTOBUF_LIBRARIES})

set(SRC_FTPSERVER  FtpServer.cc)
ADD_EXECUTABLE(server ${SRC_FTPSERVER} ${PROTO_SRCS} ${PROTO_HDRS})
add_dependencies(server ndsl)
target_link_libraries(server ndsl pthread protobuf ${PROTOBUF_LIBRARIES})