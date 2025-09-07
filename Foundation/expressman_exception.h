#pragma once
#include "framework.h"
#include "pch.h"

#include "iExceptionBase.h"
#include "libID.h"

namespace HYDRA15::Foundation::Exceptions
{
    class expressman : public referee::iExceptionBase
    {
    public:
        static struct iException_codes
        {
            static_uint expressman = 0x0000;

            // Messager
            static_uint messager = 0xA00;
            static_uint messagerRepeatedIndex = 0xA01;
            static_uint messagerIndexNotFound = 0xA02;
            static_uint messagerInvalidToken = 0xA03;

        }iExptCodes;

    private:
        static struct vslz
        {
            static_string expressman = "Unknown Expressman Exception";

        }vslz;

    public:
        expressman(
            const std::string& desp = vslz.expressman.data(),
            const referee::iException_code& code = iExptCodes.expressman
        ) noexcept;
        expressman() = delete;
        virtual ~expressman() noexcept = default;

        // 快速创建异常
        static expressman make_exception(const referee::iException_code& exptCode = iExptCodes.expressman) noexcept;

        // Messager
        static expressman MessagerUnknownException();
        static expressman MessagerRepeatedIndex();
        static expressman MessagerIndexNotFound();
        static expressman MessagerInvalidToken();
    };
}