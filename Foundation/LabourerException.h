#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class Labourer : public Referee::iExceptionBase
    {
    public:
        static struct iExceptionCodes
        {
            // 线程池
            StaticUInt threadLake = 0xA00;
            StaticUInt threadQueueFull = 0xA01;
        }iExptCodes;

    private:
        static struct Visualize
        {
            // 线程池
            StaticString thrdLakeExpt = "ThreadLake Exception";
            StaticString thrdLakeQueueFull = "ThreadLake: Task queue is full";
        }visualize;

    public:
        Labourer(
            const std::string& desp = visualize.thrdLakeExpt.data(),
            const Referee::iExceptionCode& code = iExptCodes.threadLake
        ) noexcept;
        Labourer() = delete;
        virtual ~Labourer() noexcept = default;


        // 快速创建异常
        static Labourer make_exception(const Referee::iExceptionCode& exptCode) noexcept;

        static Labourer TaskQueueFull() noexcept;

    };
}