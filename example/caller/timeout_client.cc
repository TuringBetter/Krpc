#include <iostream>
#include <string>

#include "Krpcapplication.h"
#include "Krpcchannel.h"
#include "Krpccontroller.h"
#include "user.pb.h"

int main(int argc, char** argv) {
    KrpcApplication::GetInstance()->Init(argc, argv);

    Kuser::UserServiceRpc_Stub stub(new KrpcChannel(false));

    Kuser::LoginRequest request;
    request.set_name("zhangsan");
    request.set_pwd("123456");

    Kuser::LoginResponse response;
    Krpccontroller controller;

    // 设置超时时间为 2000ms (2秒)
    controller.SetTimeout(2000);

    std::cout << "Calling Login with 2s timeout..." << std::endl;
    stub.Login(&controller, &request, &response, nullptr);

    if (controller.Failed()) {
        std::cout << "RPC failed: " << controller.ErrorText() << std::endl;
    } else {
        std::cout << "RPC success!" << std::endl;
    }

    return 0;
}
