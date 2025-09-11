#include "pch.h"
#include "archivist_exception.h"

namespace HYDRA15::Foundation::Exceptions
{
    archivist::archivist(const std::string& desp, const referee::iException_code& code) noexcept
        : referee::iExceptionBase(desp, Foundation::framework::libID.archivist, code)
    {
    }

    archivist archivist::make_exception(const referee::iException_code& exptCode) noexcept
    {
        return archivist(
            vslz.archivist.data(),
            exptCode
        );
    }

    archivist archivist::EntryUnknownExpt() noexcept
    {
        return archivist(
            vslz.entry.data(),
            iExptCodes.entry
        );
    }

    archivist archivist::EntryEmpty() noexcept
    {
        return archivist(
            vslz.entryEmpty.data(),
            iExptCodes.entryEmpty
        );
    }

    archivist archivist::EntryTypeMismatch() noexcept
    {
        return archivist(
            vslz.entryTypeMismatch.data(),
            iExptCodes.entryTypeMismatch
        );
    }

    archivist archivist::IndexUnknownExpt() noexcept
    {
        return archivist(
            vslz.index.data(),
            iExptCodes.index
        );
    }

    archivist archivist::IndexEmpty() noexcept
    {
        return archivist(
            vslz.indexEmpty.data(),
            iExptCodes.indexEmpty
        );
    }

    archivist archivist::IndexTypeMismatch() noexcept
    {
        return archivist(
            vslz.indexTypeMismatch.data(),
            iExptCodes.indexTypeMismatch
        );
    }

    archivist archivist::TabletUnknownExpt() noexcept
    {
        return archivist(
            vslz.tablet.data(),
            iExptCodes.tablet
        );
    }

    archivist archivist::TabletInvalidContainerOperation() noexcept
    {
        return archivist(
            vslz.tabletInvalidContainerOperation.data(),
            iExptCodes.tabletInvalidContainerOperation
        );
    }

    archivist archivist::TabletContainerEmpty() noexcept
    {
        return archivist(
            vslz.tabletContainerEmpty.data(),
            iExptCodes.tabletContainerEmpty
        );
    }

    archivist archivist::TabletContainerFull() noexcept
    {
        return archivist(
            vslz.tabletContainerFull.data(),
            iExptCodes.tabletContainerFull
        );
    }

    archivist archivist::TabletListRangeExceed() noexcept
    {
        return archivist(
            vslz.tabletListRangeExceed.data(),
            iExptCodes.tabletListRangeExceed
        );
    }

    archivist archivist::TabletListBadSize() noexcept
    {
        return archivist(
            vslz.tabletListBadSize.data(),
            iExptCodes.tabletListBadSize
        );
    }

    archivist archivist::RegistryUnknownExpt() noexcept
    {
        return archivist(
            vslz.registry.data(),
            iExptCodes.registry
        );
    }

    archivist archivist::RegistryTabletInvalidMaxSize() noexcept
    {
        return archivist(
            vslz.registryTabletInvalidMaxSize.data(),
            iExptCodes.registryTabletInvalidMaxSize
        );
    }

    archivist archivist::RegistryTabletFull() noexcept
    {
        return archivist(
            vslz.registryTabletFull.data(),
            iExptCodes.registryTabletFull
        );
    }

    archivist archivist::RegistryKeyExists() noexcept
    {
        return archivist(
            vslz.registryKeyExists.data(),
            iExptCodes.registryKeyExists
        );
    }

    archivist archivist::RegistryKeyNotFound() noexcept
    {
        return archivist(
            vslz.registryKeyNotFound.data(),
            iExptCodes.registryKeyNotFound
        );
    }





}