#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    class IndexBase
    {
    public:
        IndexBase() = default;
        IndexBase(const IndexBase& other) = default;
        virtual ~IndexBase() = default;

        // 核心功能：判等、比较和哈希
        virtual bool operator==(const IndexBase& other) const;
        virtual bool operator<(const IndexBase& other) const;
        virtual bool operator>(const IndexBase& other) const;
        virtual size_t hash() const;
    };

    template<typename T>
    class IndexImpl : public IndexBase
    {
        T data = T();

    public:
        IndexImpl(const T& t) : data(t) {}

        bool operator==(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const IndexImpl<T>*>(&other);
            return otherIndex && data == otherIndex->data;
        }

        bool operator<(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const IndexImpl<T>*>(&other);
            return otherIndex && data < otherIndex->data;
        }

        bool operator>(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const IndexImpl<T>*>(&other);
            return otherIndex && data > otherIndex->data;
        }

        size_t hash() const override
        {
            return std::hash<T>()(data);
        }

        operator T() const
        {
            return data;
        }
    };


}

namespace std
{
    using namespace HYDRA15::Foundation::Archivist;
    template<>
    struct hash<IndexBase>
    {
        size_t operator()(const IndexBase& k) const
        {
            return k.hash();
        }
    };
}