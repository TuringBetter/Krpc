cmake_minimum_required(VERSION 3.15)
project(grpc_example)

set(CMAKE_CXX_STANDARD 17)

# 设置可执行文件输出目录为当前目录下的 bin 文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# REQUIRED:如果找不到指定的包或模块，则停止配置并报错。
find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)
pkg_check_modules(GRPC REQUIRED grpc++ grpc)

# 定义文件名
set(PROTO_SRC user.proto)
set(PROTO_HEADER user.pb.h)
set(PROTO_CC user.pb.cc)
set(GRPC_HEADER user.grpc.pb.h)
set(GRPC_CC user.grpc.pb.cc)

# 定义生成文件的绝对路径（指向源码目录）
set(GEN_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_HEADER}" "${CMAKE_CURRENT_SOURCE_DIR}/${GRPC_HEADER}")
set(GEN_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_CC}" "${CMAKE_CURRENT_SOURCE_DIR}/${GRPC_CC}")

find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

# 【修改点 3】修改 protoc 命令，将输出路径改为源码目录
add_custom_command(
  OUTPUT ${GEN_HDRS} ${GEN_SRCS}
  COMMAND protoc
    -I "${CMAKE_CURRENT_SOURCE_DIR}"
    --grpc_out="${CMAKE_CURRENT_SOURCE_DIR}"  # 输出到源码目录
    --cpp_out="${CMAKE_CURRENT_SOURCE_DIR}"   # 输出到源码目录
    --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
    "${CMAKE_CURRENT_SOURCE_DIR}/user.proto"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/user.proto"
)

# 编译服务端
add_executable(server server.cc ${GEN_SRCS})
target_link_libraries(server ${GRPC_LIBRARIES} ${Protobuf_LIBRARIES} pthread)
# 包含路径指向源码目录（确保能找到 user.pb.h）
target_include_directories(server PRIVATE ${GRPC_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}")

# 编译客户端
add_executable(client client.cc ${GEN_SRCS})
target_link_libraries(client ${GRPC_LIBRARIES} ${Protobuf_LIBRARIES} pthread)
target_include_directories(client PRIVATE ${GRPC_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}")