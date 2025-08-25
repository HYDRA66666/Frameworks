#include "pch.h"
#include "ArchivistException.h"

namespace HYDRA15::Foundation::Exceptions
{
    Archivist::Archivist(const std::string& desp, const Referee::iExceptionCode& code) noexcept
        : Referee::iExceptionBase(desp, Foundation::LibInfo::libID.Archivist, code)
    {
    }

    Archivist Archivist::make_exception(const Referee::iExceptionCode& exptCode) noexcept
    {
        return Archivist(
            visualize.archivist.data(),
            exptCode
        );
    }

    Archivist Archivist::EntryUnknownExpt() noexcept
    {
        return Archivist(
            visualize.entry.data(),
            iExptCodes.entry
        );
    }

    Archivist Archivist::EntryEmpty() noexcept
    {
        return Archivist(
            visualize.entryEmpty.data(),
            iExptCodes.entryEmpty
        );
    }

    Archivist Archivist::EntryTypeMismatch() noexcept
    {
        return Archivist(
            visualize.entryTypeMismatch.data(),
            iExptCodes.entryTypeMismatch
        );
    }

    Archivist Archivist::IndexUnknownExpt() noexcept
    {
        return Archivist(
            visualize.index.data(),
            iExptCodes.index
        );
    }

    Archivist Archivist::IndexEmpty() noexcept
    {
        return Archivist(
            visualize.indexEmpty.data(),
            iExptCodes.indexEmpty
        );
    }

    Archivist Archivist::IndexTypeMismatch() noexcept
    {
        return Archivist(
            visualize.indexTypeMismatch.data(),
            iExptCodes.indexTypeMismatch
        );
    }

    Archivist Archivist::TabletUnknownExpt() noexcept
    {
        return Archivist(
            visualize.tablet.data(),
            iExptCodes.tablet
        );
    }

    Archivist Archivist::TabletInvalidContainerOperation() noexcept
    {
        return Archivist(
            visualize.tabletInvalidContainerOperation.data(),
            iExptCodes.tabletInvalidContainerOperation
        );
    }

    Archivist Archivist::TabletContainerEmpty() noexcept
    {
        return Archivist(
            visualize.tabletContainerEmpty.data(),
            iExptCodes.tabletContainerEmpty
        );
    }

    Archivist Archivist::TabletContainerFull() noexcept
    {
        return Archivist(
            visualize.tabletContainerFull.data(),
            iExptCodes.tabletContainerFull
        );
    }

    Archivist Archivist::TabletListRangeExceed() noexcept
    {
        return Archivist(
            visualize.tabletListRangeExceed.data(),
            iExptCodes.tabletListRangeExceed
        );
    }

    Archivist Archivist::TabletListBadSize() noexcept
    {
        return Archivist(
            visualize.tabletListBadSize.data(),
            iExptCodes.tabletListBadSize
        );
    }

    Archivist Archivist::RegistryUnknownExpt() noexcept
    {
        return Archivist(
            visualize.registry.data(),
            iExptCodes.registry
        );
    }

    Archivist Archivist::RegistryTabletInvalidMaxSize() noexcept
    {
        return Archivist(
            visualize.registryTabletInvalidMaxSize.data(),
            iExptCodes.registryTabletInvalidMaxSize
        );
    }

    Archivist Archivist::RegistryTabletFull() noexcept
    {
        return Archivist(
            visualize.registryTabletFull.data(),
            iExptCodes.registryTabletFull
        );
    }

    Archivist Archivist::RegistryKeyExists() noexcept
    {
        return Archivist(
            visualize.registryKeyExists.data(),
            iExptCodes.registryKeyExists
        );
    }

    Archivist Archivist::RegistryKeyNotFound() noexcept
    {
        return Archivist(
            visualize.registryKeyNotFound.data(),
            iExptCodes.registryKeyNotFound
        );
    }





}