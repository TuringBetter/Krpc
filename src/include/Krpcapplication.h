#ifndef _Krpcapplication_H
#define _Krpcapplication_H
#include "Krpcconfig.h"
#include "Krpcchannel.h" 
#include "Krpccontroller.h"
#include<mutex>
//Krpc基础类，负责框架的一些初始化操作
class KrpcApplication
{
public:
    static void Init(int argc,char **argv);
    static void deleteInstance();
    static KrpcApplication& GetInstance();
    static Krpcconfig&      GetConfig();
private:
    static KrpcApplication*  m_application;//全局唯一单例访问对象
    static Krpcconfig        m_config;
    static std::mutex        m_mutex;
    KrpcApplication(){}
    ~KrpcApplication(){}
    KrpcApplication(const KrpcApplication&)=delete;
    KrpcApplication(KrpcApplication&&)=delete;
};
#endif 
