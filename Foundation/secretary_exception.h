#pragma once
#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "libID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class secretary : public referee::iExceptionBase
    {
    public:
        static struct iException_codes
        {
            static_uint secretary = 0x0000;

            // 打印中心
            static_uint printCenter = 0xA00;
            static_uint printBtmMsgFull = 0xA01;
            static_uint printBtmMsgNotFound = 0xA02;
            static_uint printBtmMsgBadToken = 0xA03;
        }iExptCodes;

    private:
        static struct visualize
        {
            static_string secretary = "Unknown Secretary Exception";

            // 打印中心
            static_string printCenter = "Unknown PrintCenter Exception";
            static_string printBtmMsgFull = "PrintCenter: Bottom message limit reached";
            static_string printBtmMsgNotFound = "PrintCenter: Bottom message ID not found";
            static_string printBtmMsgBadToken = "PrintCenter: Bottom message token mismatch";
        }vslz;

    public:
        secretary(
            const std::string& desp = vslz.secretary.data(),
            const referee::iException_code& code = iExptCodes.secretary
        ) noexcept;
        secretary() = delete;
        virtual ~secretary() noexcept = default;


        // 快速创建异常
        static secretary make_exception(const referee::iException_code& exptCode) noexcept;

        static secretary PrintCenterUnknown() noexcept;
        static secretary PrintCenterBtmMsgFull() noexcept;
        static secretary PrintCenterBtmMsgNotFound() noexcept;
        static secretary PrintCenterBtmMsgBadToken() noexcept;


    };
}