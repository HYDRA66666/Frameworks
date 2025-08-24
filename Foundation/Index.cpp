#include "pch.h"
#include "Index.h"

namespace HYDRA15::Foundation::Archivist
{
    Index::Index(const Index& other)
        : pImpl(std::dynamic_pointer_cast<EntryBase>(other.pImpl)->clone())
    {
    }

    Index::Index(Index&& other)
        :pImpl(std::move(other.pImpl))
    {
    }

    bool Index::operator==(const Index& other) const
    {
        if (!pImpl || !other.pImpl)
            throw Exceptions::Archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<IndexBase>(other.pImpl);
        return thisImpl->operator==(*otherImpl);
    }

    bool Index::operator<(const Index& other) const
    {
        if(!pImpl || !other.pImpl)
            throw Exceptions::Archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<IndexBase>(other.pImpl);
        return thisImpl->operator<(*otherImpl);
    }

    size_t Index::hash() const
    {
        if(!pImpl)
            throw Exceptions::Archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<IndexBase>(pImpl);
        return thisImpl->hash();
    }

    std::string Index::info() const
    {
        if (!pImpl)
            return visualize.indexEmpty.data();
        return std::format(
            visualize.index.data(),
            pImpl->info()
        );
    }

}