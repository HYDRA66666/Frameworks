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
            return visualize.emptyEntry.data();
        return std::format(
            visualize.entry.data(),
            pImpl->info()
        );
    }

    std::ostream& Entry::operator<<(std::ostream& os) const
    {
        if(!pImpl)
            os << visualize.emptyEntry.data();
        else
            os << pImpl->info();
        return os;
    }
}