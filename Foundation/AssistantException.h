#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class Assistant : public Referee::iExceptionBase
    {
    public:
        static struct iExceptionCodes
        {
            StaticUInt assistant = 0x0000;

            // DateTime
            StaticUInt dateTime = 0xA00;
            StaticUInt dateTimeInvalidTimeZone = 0xA01;
        }iExptCodes;

    private:
        static struct Visualize
        {
            StaticString assistant = "Unknown Assistant Exception";

            // DateTime
            StaticString dateTime = "Unknown DateTime Exception";
            StaticString dateTimeInvalidTimeZone = "DateTime: Invalid Time Zone";

        }visualize;

    public:
        Assistant(
            const std::string& desp = visualize.assistant.data(),
            const Referee::iExceptionCode& code = iExptCodes.assistant
        ) noexcept;
        Assistant() = delete;
        virtual ~Assistant() noexcept = default;

        // 快速创建异常
        static Assistant make_exception(const Referee::iExceptionCode& exptCode = iExptCodes.assistant) noexcept;

        // DateTime
        static Assistant DateTimeUnknownException();
        static Assistant DateTimeInvalidTimeZone();
    };
}