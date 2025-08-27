#include "pch.h"
#include "SecretaryException.h"

namespace HYDRA15::Foundation::Exceptions
{
    Secretary::Secretary(const std::string& desp, const Referee::iExceptionCode& code) noexcept
        : Referee::iExceptionBase(desp, Foundation::LibInfo::libID.Secretary, code)
    {
    }

    Secretary Secretary::make_exception(const Referee::iExceptionCode& exptCode) noexcept
    {
        return Secretary(
            visualize.secretary.data(),
            exptCode
        );
    }

    Secretary Secretary::PrintCenterUnknown() noexcept
    {
        return Secretary(
            visualize.printCenter.data(),
            iExptCodes.printCenter
        );
    }

    Secretary Secretary::PrintCenterBtmMsgFull() noexcept
    {
        return Secretary(
            visualize.printBtmMsgFull.data(),
            iExptCodes.printBtmMsgFull
        );
    }

    Secretary Secretary::PrintCenterBtmMsgNotFound() noexcept
    {
        return Secretary(
            visualize.printBtmMsgNotFound.data(),
            iExptCodes.printBtmMsgNotFound
        );
    }

    Secretary Secretary::PrintCenterBtmMsgBadToken() noexcept
    {
        return Secretary(
            visualize.printBtmMsgBadToken.data(),
            iExptCodes.printBtmMsgBadToken
        );
    }

}