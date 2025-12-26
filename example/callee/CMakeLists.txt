#获取服务端的源文件
# file(GLOB SERVER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

#获取protobuf生成的.cc
file(GLOB PROTO_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen/*.pb.cc)

#创建服务端可执行文件
add_executable(server Kserver.cc ${PROTO_SRCS})
add_executable(timeout_server timeout_server.cc ${PROTO_SRCS})

#链接必要的库，尤其是example中生成的静态库
target_link_libraries(server krpc_core ${LIBS})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen)

#设置编译选项
target_compile_options(server PRIVATE -std=c++11 -Wall)

# 设置 server 可执行文件输出目录
set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#链接必要的库
target_link_libraries(timeout_server krpc_core ${LIBS})
target_include_directories(timeout_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen)

#设置编译选项
target_compile_options(timeout_server PRIVATE -std=c++11 -Wall)

# 设置 timeout_server 可执行文件输出目录
set_target_properties(timeout_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
