#pragma once
#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "LibID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class Secretary : public Referee::iExceptionBase
    {
    public:
        static struct iExceptionCodes
        {
            StaticUInt secretary = 0x0000;

            // 打印中心
            StaticUInt printCenter = 0xA00;
            StaticUInt printBtmMsgFull = 0xA01;
            StaticUInt printBtmMsgNotFound = 0xA02;
            StaticUInt printBtmMsgBadToken = 0xA03;
        }iExptCodes;

    private:
        static struct Visualize
        {
            StaticString secretary = "Unknown Secretary Exception";

            // 打印中心
            StaticString printCenter = "Unknown PrintCenter Exception";
            StaticString printBtmMsgFull = "PrintCenter: Bottom message limit reached";
            StaticString printBtmMsgNotFound = "PrintCenter: Bottom message ID not found";
            StaticString printBtmMsgBadToken = "PrintCenter: Bottom message token mismatch";
        }visualize;

    public:
        Secretary(
            const std::string& desp = visualize.secretary.data(),
            const Referee::iExceptionCode& code = iExptCodes.secretary
        ) noexcept;
        Secretary() = delete;
        virtual ~Secretary() noexcept = default;


        // 快速创建异常
        static Secretary make_exception(const Referee::iExceptionCode& exptCode) noexcept;

        static Secretary PrintCenterUnknown() noexcept;
        static Secretary PrintCenterBtmMsgFull() noexcept;
        static Secretary PrintCenterBtmMsgNotFound() noexcept;
        static Secretary PrintCenterBtmMsgBadToken() noexcept;


    };
}