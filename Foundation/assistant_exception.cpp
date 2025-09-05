#include "pch.h"
#include "assistant_exception.h"

namespace HYDRA15::Foundation::Exceptions
{
    assistant::assistant(const std::string& desp, const referee::iException_code& code) noexcept
        :referee::iException_base(desp, LibInfo::libID.assistant, code)
    {
    }

    assistant assistant::make_exception(const referee::iException_code& code) noexcept
    {
        return assistant(vslz.assistant.data(), code);
    }

    assistant assistant::DateTimeUnknownException()
    {
        return assistant(vslz.dateTime.data(), iExptCodes.dateTime);
    }

    assistant assistant::DateTimeInvalidTimeZone()
    {
        return assistant(vslz.dateTimeInvalidTimeZone.data(), iExptCodes.dateTimeInvalidTimeZone);
    }


}