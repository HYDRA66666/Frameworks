#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry::Entry(const Entry& other)
        : pImpl(other.pImpl ? other.pImpl->clone() : nullptr)
    {
    }

    Entry::Entry(Entry&& other)
        : pImpl(std::move(other.pImpl))
    {
    }

    Entry& Entry::operator=(const Entry& other)
    {
        pImpl = other.pImpl ? other.pImpl->clone() : nullptr;
        return *this;
    }

    Entry& Entry::operator=(Entry&& other)
    {
        pImpl = std::move(other.pImpl);
        return *this;
    }

    std::string Entry::info() const
    {
        if (!pImpl)
            return infoEmpty.data();
        return pImpl->info();
    }

    std::ostream& Entry::operator<<(std::ostream& os) const
    {
        if(!pImpl)
            os << infoEmpty.data();
        else
            os << pImpl->info();
        return os;
    }
}