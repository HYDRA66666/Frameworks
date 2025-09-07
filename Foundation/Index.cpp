#include "pch.h"
#include "index.h"

namespace HYDRA15::Foundation::archivist
{
    index::index(const index& other)
        : pImpl(std::dynamic_pointer_cast<entry_base>(other.pImpl)->clone())
    {
    }

    index::index(index&& other) noexcept
        :pImpl(std::move(other.pImpl))
    {
    }

    bool index::operator==(const index& other) const
    {
        if (!pImpl || !other.pImpl)
            throw Exceptions::archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<index_base>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<index_base>(other.pImpl);
        return thisImpl->operator==(*otherImpl);
    }

    bool index::operator<(const index& other) const
    {
        if(!pImpl || !other.pImpl)
            throw Exceptions::archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<index_base>(pImpl);
        auto otherImpl = std::dynamic_pointer_cast<index_base>(other.pImpl);
        return thisImpl->operator<(*otherImpl);
    }

    size_t index::hash() const
    {
        if(!pImpl)
            throw Exceptions::archivist::IndexEmpty();
        auto thisImpl = std::dynamic_pointer_cast<index_base>(pImpl);
        return thisImpl->hash();
    }

    std::string index::info() const
    {
        if (!pImpl)
            return vslz.indexEmpty.data();
        return std::format(
            vslz.index.data(),
            pImpl->info()
        );
    }

}