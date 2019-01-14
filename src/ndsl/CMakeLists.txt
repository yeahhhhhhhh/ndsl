##
# @file CMakeLists.txt
# @brief
# ndsl目录的cmake文件
#
# @author niexw
# @email xiaowen.nie.cn@gmail.com
#

include_directories(${CMAKE_SOURCE_DIR}/thirdlib)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/ndsl)
include_directories(${CMAKE_SOURCE_DIR}/include/ndsl/utils)
include_directories(${CMAKE_SOURCE_DIR}/include/ndsl/net)
add_subdirectory(net)
add_subdirectory(utils)


aux_source_directory(./net/ LIB_NDSL_SRC)
aux_source_directory(./utils LIB_NDSL_SRC1)
list(APPEND LIB_NDSL_SRC ${LIB_NDSL_SRC1})
add_library(ndsl ${LIB_NDSL_SRC})
target_link_libraries(ndsl uuid)

#生成libplugin.so
 #set(LIB_SRC utils/Plugin.cc)
 #set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)  

 #add_library(libplugin SHARED ${LIB_SRC})
 #set_target_properties(libplugin PROPERTIES OUTPUT_NAME "plugin")

 #set(CLIENT_SRC utils/Clientplugin.cc)
 #set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)  

 #add_library(clientplugin SHARED ${CLIENT_SRC})
 #set_target_properties(clientplugin PROPERTIES OUTPUT_NAME "clientplugin")
