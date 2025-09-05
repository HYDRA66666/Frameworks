#include "pch.h"
#include "entry.h"

namespace HYDRA15::Foundation::archivist
{
    entry::entry(const entry& other)
        : pImpl(other.pImpl ? other.pImpl->clone() : nullptr)
    {
    }

    entry::entry(entry&& other)
        : pImpl(std::move(other.pImpl))
    {
    }

    entry& entry::operator=(const entry& other)
    {
        pImpl = other.pImpl ? other.pImpl->clone() : nullptr;
        return *this;
    }

    entry& entry::operator=(entry&& other)
    {
        pImpl = std::move(other.pImpl);
        return *this;
    }

    std::string entry::info() const
    {
        if (!pImpl)
            return vslz.emptyEntry.data();
        return std::format(
            vslz.entry.data(),
            pImpl->info()
        );
    }

    std::ostream& entry::operator<<(std::ostream& os) const
    {
        if(!pImpl)
            os << vslz.emptyEntry.data();
        else
            os << pImpl->info();
        return os;
    }
}