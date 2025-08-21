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

    Archivist Archivist::IndexUnknownExpt()
    {
        return Archivist(
            visualize.index.data(),
            iExptCodes.index
        );
    }

    Archivist Archivist::IndexTypeMismatch()
    {
        return Archivist(
            visualize.indexTypeMismatch.data(),
            iExptCodes.indexTypeMismatch
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

    Archivist Archivist::EntryNotEndpoint() noexcept
    {
        return Archivist(
            visualize.entryNotEndpoint.data(),
            iExptCodes.entryNotEndpoint
        );
    }

    Archivist Archivist::EntryNotContainer() noexcept
    {
        return Archivist(
            visualize.entryNotContainer.data(),
            iExptCodes.entryNotContainer
        );
    }

    Archivist Archivist::EntryDataTypeMismatch() noexcept
    {
        return Archivist(
            visualize.entryDataTypeMismatch.data(),
            iExptCodes.entryDataTypeMismatch
        );
    }

    Archivist Archivist::EntryInvalidContainerOperation() noexcept
    {
        return Archivist(
            visualize.entryInvalidContainerOperation.data(),
            iExptCodes.entryInvalidContainerOperation
        );
    }

    Archivist Archivist::EntryElementNotFound() noexcept
    {
        return Archivist(
            visualize.EntryElementNotFound.data(),
            iExptCodes.EntryElementNotFound
        );
    }

    Archivist Archivist::EntryContainerEmpty() noexcept
    {
        return Archivist(
            visualize.EntryContainerEmpty.data(),
            iExptCodes.EntryContainerEmpty
        );
    }

    Archivist Archivist::EntryContainerFull() noexcept
    {
        return Archivist(
            visualize.EntryContainerFull.data(),
            iExptCodes.EntryContainerFull
        );
    }

    Archivist Archivist::EntryInvalidContainerSize() noexcept
    {
        return Archivist(
            visualize.EntryInvalidContainerSize.data(),
            iExptCodes.EntryInvalidContainerSize
        );
    }

}