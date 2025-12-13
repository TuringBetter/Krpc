#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "user.grpc.pb.h" // protoc 生成的头文件

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using Kuser::UserServiceRpc;
using Kuser::LoginRequest;
using Kuser::LoginResponse;
using Kuser::RegisterRequest;
using Kuser::RegisterResponse;

// 业务实现类
class UserServiceImpl final : public UserServiceRpc::Service {
    // 实现 Login 方法
    Status Login(ServerContext* context, const LoginRequest* request,
                  LoginResponse* reply) override {
        // 获取请求参数
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 执行本地业务（对应原 Kserver.cc 中的打印逻辑）
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;

        // 填写响应
        auto* result = reply->mutable_result();
        result->set_errcode(0);
        result->set_errmsg("");
        reply->set_success(true); // 模拟登录成功

        return Status::OK;
    }

    // Register 方法留空示例
    Status Register(ServerContext* context, const RegisterRequest* request,
                    RegisterResponse* reply) override {
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    UserServiceImpl service;

    ServerBuilder builder;
    // 监听端口，不使用 SSL (Insecure)
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // 注册服务
    builder.RegisterService(&service);
    // 构建并启动
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    // 阻塞等待
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}