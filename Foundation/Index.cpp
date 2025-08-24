#include "pch.h"
#include "Index.h"

namespace HYDRA15::Foundation::Archivist
{
    Index::Index(const Index& other)
        : pImpl(std::dynamic_pointer_cast<EntryBase>(other.pImpl)->clone())
    {
    }

    bool Index::operator==(const Index& other) const
    {
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<IndexBase>(other.pImpl);
        return thisImpl->operator==(*otherImpl);
    }

    bool Index::operator<(const Index& other) const
    {
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<IndexBase>(other.pImpl);
        return thisImpl->operator<(*otherImpl);
    }

    size_t Index::hash() const
    {
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        return thisImpl->hash();
    }

    std::string Index::info() const
    {
        return std::format(
            visualize.index.data(),
            pImpl->info()
        );
    }

}