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
        return Archivist(visualize.entryExpt.data(), exptCode);
    }

    Archivist Archivist::EntryEmpty() noexcept
    {
        return Archivist(visualize.entryEmpty.data(), iExptCodes.entryEmpty);
    }

    Archivist Archivist::EntryDataTypeMismatch() noexcept
    {
        return Archivist(visualize.entryDataTypeMismatch.data(), iExptCodes.entryDataTypeMismatch);
    }

    Archivist Archivist::EntryNotContainer() noexcept
    {
        return Archivist(visualize.entryNotContainer.data(), iExptCodes.entryNotContainer);
    }

    Archivist Archivist::EntryInvalidContainerOperation() noexcept
    {
        return Archivist(visualize.entryInvalidContainerOperation.data(), iExptCodes.entryInvalidContainerOperation);
    }

    Archivist Archivist::EntryKeyTypeMismatch() noexcept
    {
        return Archivist(visualize.entryKeyTypeMismatch.data(), iExptCodes.entryKeyTypeMismatch);
    }

    Archivist Archivist::EntryContainerIsEmpty() noexcept
    {
        return Archivist(visualize.entryContainerIsEmpty.data(),iExptCodes.entryContainerIsEmpty);
    }

    Archivist Archivist::EntryBadKey() noexcept
    {
        return Archivist(visualize.entryBadKey.data(),iExptCodes.entryBadKey);
    }

}