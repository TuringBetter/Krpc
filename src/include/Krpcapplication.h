#pragma once

#include "Krpcconfig.h"
#include "Singleton.h"

// Krpc基础类，负责框架的一些初始化操作
class KrpcApplication : public Singleton<KrpcApplication> {
public:
    void Init(int argc, char** argv);
    Krpcconfig& GetConfig() { return m_config; }

private:
    Krpcconfig m_config;
};
