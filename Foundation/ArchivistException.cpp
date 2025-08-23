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



}