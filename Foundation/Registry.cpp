#include "pch.h"
#include "Registry.h"

namespace HYDRA15::Foundation::Archivist
{
    void NotALock::lock(){}

    void NotALock::unlock() {}

    bool NotALock::try_lock() { return true; }
}