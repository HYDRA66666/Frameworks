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



}