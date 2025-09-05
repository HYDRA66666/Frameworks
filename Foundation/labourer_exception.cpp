#include "pch.h"
#include "labourer_exception.h"

namespace HYDRA15::Foundation::Exceptions
{
    labourer::labourer(const std::string& desp, const referee::iException_code& code) noexcept
        : referee::iException_base(desp, Foundation::LibInfo::libID.labourer, code)
    {
    }

    labourer labourer::make_exception(const referee::iException_code& exptCode) noexcept
    {
        return labourer(
            vslz.thrdLakeExpt.data(),
            exptCode
        );
    }

    labourer labourer::TaskQueueFull() noexcept
    {
        return labourer(
            vslz.thrdLakeQueueFull.data(),
            iExptCodes.threadQueueFull
        );
    }
}