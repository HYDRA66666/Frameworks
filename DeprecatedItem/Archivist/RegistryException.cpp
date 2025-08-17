#include "pch.h"
#include "RegistryException.h"

namespace HYDRA15::Frameworks::Archivist::iExceptions
{
    Registry::Registry(const std::string& desp, const unsigned int& code) noexcept
        :iExceptionBase(desp, Foundation::LibInfomation::libID.Archivist, code)
    {
    }

    Registry Registry::make_exception(unsigned int exptCode)noexcept
    {
        return Registry(visualize.regExpt.data(), exptCode);
    }

    Registry Registry::TabletInvalidMaxSize() noexcept
    {
        return Registry(visualize.regTabInvalidMaxSize.data(), iExptCodes.regiestTabInvalidMaxSize);
    }

    Registry Registry::TabletFull() noexcept
    {
        return Registry(visualize.regTabFull.data(),iExptCodes.registryTabFull);
    }

    Registry Registry::KeyExists() noexcept
    {
        return Registry(visualize.regKeyExists.data(),iExptCodes.registryKeyExists);
    }

    Registry Registry::KeyNotFound() noexcept
    {
        return Registry(visualize.regKeyNotFound.data(), iExptCodes.registryKeyNotFound);
    }

    Registry Registry::KeyOverflow() noexcept
    {
        return Registry(visualize.regKeyOverflow.data(), iExptCodes.registryKeyOverflow);
    }




}