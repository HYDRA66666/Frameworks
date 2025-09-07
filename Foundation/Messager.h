#pragma once
#include "framework.h"
#include "pch.h"

#include "basic_messager.h"

namespace HYDRA15::Foundation::expressman
{
    // 全局消息中心
    class Messager :public basic_messager
    {
    private:
        Messager() = default;
        Messager(const Messager&) = delete;

    public:
        static Messager& get_instance();
        ~Messager() = default;
    };
}