#include "Krpcapplication.h"
#include "../user.pb.h"
#include "Krpccontroller.h"
#include <iostream>
#include <atomic>
#include <chrono>
#include "KrpcLogger.h"

void send_single_request(){
    Kuser::UserServiceRpc_Stub stub(new KrpcChannel(false));

    Kuser::LoginRequest request;
    request.set_name("zhangsan");
    request.set_pwd("123456");

    Kuser::LoginResponse response;
    Krpccontroller controller;
    stub.Login(&controller, &request, &response, nullptr);

    if(controller.Failed()){
        std::cout << controller.ErrorText() << std::endl;
    }

    if(int{} != response.result().errcode()){
        std::cout << "rpc login response error : " << response.result().errmsg() << std::endl;
    }

    std::cout << "rpc login response success:" << response.success() << std::endl;

}

int main(int argc, char **argv){
    KrpcApplication::Init(argc, argv);
    KrpcLogger logger("MyRPC");
    send_single_request();
    return 0;
}