#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    bool IndexBase::operator==(const IndexBase& other) const
    {
        return false;
    }

    bool IndexBase::operator<(const IndexBase& other) const
    {
        return false;
    }

    bool IndexBase::operator>(const IndexBase& other) const
    {
        return false;
    }

    size_t IndexBase::hash() const
    {
        return 0;
    }


}