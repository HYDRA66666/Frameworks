#include "pch.h"
#include "LabourerException.h"

namespace HYDRA15::Foundation::Exceptions
{
    ThreadLake::ThreadLake(const std::string& desp, const Referee::iExceptionCode& code) noexcept
        : Referee::iExceptionBase(desp, Foundation::LibInfo::libID.Labourer, code)
    {
    }

    ThreadLake ThreadLake::make_exception(const Referee::iExceptionCode& exptCode) noexcept
    {
        return ThreadLake(
            visualize.thrdLakeExpt.data(),
            exptCode
        );
    }

    ThreadLake ThreadLake::TaskQueueFull() noexcept
    {
        return ThreadLake(
            visualize.thrdLakeQueueFull.data(),
            iExptCodes.threadQueueFull
        );
    }
}