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

    std::string Index::info() const
    {
#define TRY(Type) \
        try { \
            return std::format(visualize.knownIndex, typeid(Type).name(), static_cast<Type>(*this)); \
        } catch (...) { \
        }

        TRY(int);
        TRY(unsigned int);
        TRY(long long);
        TRY(unsigned long long);
        TRY(float);
        TRY(double);
        TRY(std::string);

#undef TRY

        return std::format(visualize.unknownIndex, typeid(*pidxb).name());
    }

}