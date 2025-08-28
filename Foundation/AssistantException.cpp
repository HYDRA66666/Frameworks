#include "pch.h"
#include "AssistantException.h"

namespace HYDRA15::Foundation::Exceptions
{
    Assistant::Assistant(const std::string& desp, const Referee::iExceptionCode& code) noexcept
        :Referee::iExceptionBase(desp, LibInfo::libID.Assistant, code)
    {
    }

    Assistant Assistant::make_exception(const Referee::iExceptionCode& code) noexcept
    {
        return Assistant(visualize.assistant.data(), code);
    }

    Assistant Assistant::DateTimeUnknownException()
    {
        return Assistant(visualize.dateTime.data(), iExptCodes.dateTime);
    }

    Assistant Assistant::DateTimeInvalidTimeZone()
    {
        return Assistant(visualize.dateTimeInvalidTimeZone.data(), iExptCodes.dateTimeInvalidTimeZone);
    }


}