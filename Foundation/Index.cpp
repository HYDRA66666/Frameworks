#include "pch.h"
#include "Index.h"

namespace HYDRA15::Foundation::Archivist
{
    bool IndexBase::operator==(const IndexBase& other) const
    {
        return this == &other;
    }

    size_t IndexBase::hash() const
    {
        return 0;
    }


    Index::Index(const Index& other)
        : pidxb(other.pidxb)
    {
    }

    bool Index::operator==(const Index& other) const
    {
        return pidxb->operator==(*other.pidxb);
    }

    bool Index::operator<(const Index& other) const
    {
        return pidxb->operator<(*other.pidxb);
    }

    bool Index::operator>(const Index& other) const
    {
        return pidxb->operator>(*other.pidxb);
    }

    size_t Index::hash() const
    {
        return pidxb->hash();
    }

}