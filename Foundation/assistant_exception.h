#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "libID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class assistant : public referee::iExceptionBase
    {
    public:
        static struct iException_codes
        {
            static_uint assistant = 0x0000;

            // DateTime
            static_uint dateTime = 0xA00;
            static_uint dateTimeInvalidTimeZone = 0xA01;
        }iExptCodes;

    private:
        static struct vslz
        {
            static_string assistant = "Unknown Assistant Exception";

            // DateTime
            static_string dateTime = "Unknown DateTime Exception";
            static_string dateTimeInvalidTimeZone = "DateTime: Invalid Time Zone";

        }vslz;

    public:
        assistant(
            const std::string& desp = vslz.assistant.data(),
            const referee::iException_code& code = iExptCodes.assistant
        ) noexcept;
        assistant() = delete;
        virtual ~assistant() noexcept = default;

        // 快速创建异常
        static assistant make_exception(const referee::iException_code& exptCode = iExptCodes.assistant) noexcept;

        // DateTime
        static assistant DateTimeUnknownException();
        static assistant DateTimeInvalidTimeZone();
    };
}