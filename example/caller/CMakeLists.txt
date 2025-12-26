#获取客户端的源文件
#压测客户端
file(GLOB Client_Batch_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Kclient.cc)
#单次请求客户端
file(GLOB Client_Once_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/Kclient_once.cc)

#获取protobuf生成的.cc
file(GLOB PROTO_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen/*.pb.cc)

#创建压测客户端可执行文件
add_executable(client ${Client_Batch_SRCS} ${PROTO_SRCS})
#创建单次请求客户端可执行文件
add_executable(client_once ${Client_Once_SRCS} ${PROTO_SRCS})

#链接必要的库，尤其是example中生成的静态库
target_link_libraries(client krpc_core ${LIBS})
target_link_libraries(client_once krpc_core ${LIBS})
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen)
target_include_directories(client_once PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../proto_gen)

# 设置编译选项
target_compile_options(client PRIVATE -std=c++11 -Wall)

# 设置 client 可执行文件输出目录
set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置 client_once 可执行文件输出目录
set_target_properties(client_once PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
