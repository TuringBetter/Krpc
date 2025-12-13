#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "user.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using Kuser::UserServiceRpc;
using Kuser::LoginRequest;
using Kuser::LoginResponse;

class UserServiceClient {
 public:
  UserServiceClient(std::shared_ptr<Channel> channel)
      : stub_(UserServiceRpc::NewStub(channel)) {}

  // 封装调用逻辑
  void Login(const std::string& name, const std::string& pwd) {
    // 1. 准备请求
    LoginRequest request;
    request.set_name(name);
    request.set_pwd(pwd);

    // 2. 准备响应容器和上下文
    LoginResponse reply;
    ClientContext context;

    // 3. 发起 RPC 调用
    Status status = stub_->Login(&context, request, &reply);

    // 4. 处理结果
    if (status.ok()) {
      // 对应原项目中的响应判断逻辑
      if (reply.result().errcode() == 0) {
          std::cout << "rpc login response success:" << reply.success() << std::endl;
      } else {
          std::cout << "rpc login response error : " << reply.result().errmsg() << std::endl;
      }
    } else {
      std::cout << "Rpc failed: " << status.error_code() << ": " << status.error_message()
                << std::endl;
    }
  }

 private:
  std::unique_ptr<UserServiceRpc::Stub> stub_;
};

int main(int argc, char** argv) {
  // 创建连接到 localhost:50051 的 Channel
  UserServiceClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  
  std::cout << "Sending Login Request..." << std::endl;
  // 发送与原项目相同的测试数据
  client.Login("zhangsan", "123456");

  return 0;
}