#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    class IndexBase
    {
    public:
        virtual ~IndexBase() = default;

        // 核心功能：判等、比较和哈希
        virtual bool operator==(const IndexBase& other) const = 0;
        virtual bool operator<(const IndexBase& other) const = 0;
        virtual bool operator>(const IndexBase& other) const = 0;
        virtual size_t hash() const = 0;
    };

    template<typename T>
    class Index : public IndexBase
    {
        T data = T();

    public:
        Index(const T& t) : data(t) {}

        bool operator==(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const Index<T>*>(&other);
            return otherIndex && data == otherIndex->data;
        }

        bool operator<(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const Index<T>*>(&other);
            return otherIndex && data < otherIndex->data;
        }

        bool operator>(const IndexBase& other) const override
        {
            const auto* otherIndex = dynamic_cast<const Index<T>*>(&other);
            return otherIndex && data > otherIndex->data;
        }

        size_t hash() const override
        {
            return std::hash<T>()(data);
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