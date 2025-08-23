#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    std::string EntryBase::info() const
    {
        return visualize.unknownTypeInfoFormat.data();
    }

    Entry::Entry(const Entry& other)
        :pImpl(other.pImpl ? other.pImpl->clone() : nullptr)
    {
    }

    Entry::Entry(Entry&& other) 
        :pImpl(std::move(other.pImpl))
    {
    }

    std::string Entry::info() const
    {
        if (!pImpl)
            return visualize.emptyInfo.data();
        return pImpl->info();
    }
}