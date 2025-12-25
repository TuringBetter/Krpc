#ifndef _zookeeperutil_h_
#define _zookeeperutil_h_

#include <semaphore.h>
#include <zookeeper/zookeeper.h>

#include <string>

// 封装的zk客户端
class ZkClient {
public:
    ZkClient();
    ~ZkClient();
    // 建立连接（处理了异步回调）。
    // zkclient启动连接zkserver
    void Start();
    // 注册服务（利用临时节点特性实现心跳/存活检测）。
    // 在zkserver中创建一个节点，根据指定的path
    void Create(const char* path, const char* data, int datalen, int state = 0);
    // 发现服务（获取服务提供者的地址）。
    // 根据参数指定的znode节点路径，或者znode节点值
    std::string GetData(const char* path);

private:
    // Zk的客户端句柄
    zhandle_t* m_zhandle;
};
#endif
