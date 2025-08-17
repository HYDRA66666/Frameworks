#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    static struct iExceptionCodes
    {
        // 线程池
        StaticUInt threadLake = 0xA00;
        StaticUInt threadQueueFull = 0xA01;
    }iExptCodes;

    static struct Visualize
    {
        // 线程池
        StaticString thrdLakeExpt = "ThreadLake Exception";
        StaticString thrdLakeQueueFull = "ThreadLake: Task queue is full";
    }visualize;

    class ThreadLake : public Referee::iExceptionBase
    {
    public:
        ThreadLake(
            const std::string& desp = visualize.thrdLakeExpt.data(),
            const Referee::iExceptionCode& code = Exceptions::iExptCodes.threadLake
        ) noexcept;
        ThreadLake() = delete;
        virtual ~ThreadLake() noexcept = default;


        // 快速创建异常
        static ThreadLake make_exception(const Referee::iExceptionCode& exptCode) noexcept;

        static ThreadLake TaskQueueFull() noexcept;

    };
}