#pragma once
#include <iostream>
#include <memory>
#include <mutex>
template <typename T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton<T> &) = delete;
    Singleton &operator=(const Singleton<T> &st) = delete;
    static std::shared_ptr<T> _instance;

public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            // why not make_shared?
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }

    void PrintAddress() { std::cout << _instance.get() << std::endl; }

    ~Singleton() { std::cout << "this is singleton destruct" << std::endl; }
};

/*
 * 静态成员的初始化：
 * 如果是不是模板类就放在类里面
 * 如果是模板类就放在类外面
 **/
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
