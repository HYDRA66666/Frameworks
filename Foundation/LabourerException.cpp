#include "pch.h"
#include "LabourerException.h"
#include "SecretaryException.h"

namespace HYDRA15::Foundation::Exceptions
{
    Labourer::Labourer(const std::string& desp, const Referee::iExceptionCode& code) noexcept
        : Referee::iExceptionBase(desp, Foundation::LibInfo::libID.Labourer, code)
    {
    }

    Labourer Labourer::make_exception(const Referee::iExceptionCode& exptCode) noexcept
    {
        return Labourer(
            visualize.thrdLakeExpt.data(),
            exptCode
        );
    }

    Labourer Labourer::TaskQueueFull() noexcept
    {
        return Labourer(
            visualize.thrdLakeQueueFull.data(),
            iExptCodes.threadQueueFull
        );
    }
}