#ifndef _Krpcchannel_h_
#define _Krpcchannel_h_
/**
 * KrpcChannel 是 RPC 框架在客户端（Caller）的核心组件。
 * 负责将用户调用的本地方法（如 stub.Login()）转换为网络请求发送出去，并接收服务端的响应。
 *
 * 继承自 google::protobuf::RpcChannel，这是 Protobuf 为 RPC 定义的标准抽象接口。
 * 任何想要使用 Protobuf 生成的 Stub 类的 RPC 框架，都必须实现这个接口中的 CallMethod 方法。
 * 
 * 模块作用
 * 统一通信入口：它是所有 RPC 调用的底层入口。无论你调用 Login 还是 Register，最终都会走到 CallMethod。
 * 
 * 服务发现：负责与 ZooKeeper 交互，查询目标服务所在的 IP 和端口。
 *
 * 协议封装：将请求对象（Request）和元数据（Header）序列化，按照自定义的通信协议组装成字节流。
 *
 * 网络传输：负责 TCP 连接的建立、数据的发送（send）和接收（recv）。
 */
#include <google/protobuf/service.h>
#include "zookeeperutil.h"
class KrpcChannel : public google::protobuf::RpcChannel
{
public:
    KrpcChannel(bool connectNow);
    virtual ~KrpcChannel(){}
    void CallMethod(const ::google::protobuf::MethodDescriptor *method,
                    ::google::protobuf::RpcController *controller,
                    const ::google::protobuf::Message *request,
                    ::google::protobuf::Message *response,
                    ::google::protobuf::Closure *done) override; // override可以验证是否是虚函数
private:
    std::string service_name;
    std::string method_name;
    std::string m_ip;
    uint16_t    m_port;
    int         m_idx;      // 用来划分服务器ip和port的下标
    int         m_clientfd; // 存放客户端套接字

    bool newConnect(const char *ip, uint16_t port);
    std::string QueryServiceHost(ZkClient *zkclient, std::string service_name, std::string method_name, int &idx);
};
#endif
