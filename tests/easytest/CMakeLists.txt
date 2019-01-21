# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(easyserver server.cc)
add_dependencies(easyserver ndsl)
target_link_libraries(easyserver ndsl pthread)

add_executable(easyclient client.cc)
add_dependencies(easyclient ndsl)
target_link_libraries(easyclient ndsl pthread)