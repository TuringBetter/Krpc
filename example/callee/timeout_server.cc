#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "Krpcapplication.h"
#include "Krpcprovider.h"
#include "user.pb.h"

class UserService : public Kuser::UserServiceRpc {
public:
    bool Login(std::string name, std::string pwd) {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
        // 模拟耗时操作，睡眠 5 秒
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return true;
    }

    void Login(::google::protobuf::RpcController* controller,
               const ::Kuser::LoginRequest* request,
               ::Kuser::LoginResponse* response,
               ::google::protobuf::Closure* done) override {
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool login_result = Login(name, pwd);

        Kuser::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        done->Run();
    }
};

int main(int argc, char** argv) {
    KrpcApplication::GetInstance()->Init(argc, argv);

    KrpcProvider provider;
    provider.NotifyService(new UserService());

    provider.Run();

    return 0;
}
