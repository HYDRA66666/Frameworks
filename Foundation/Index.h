#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    // 可以存储任意数据类型的索引
    // 注意：索引的实际类型必须支持比较和哈希

    class IndexBase
    {
    public:
        virtual ~IndexBase() = default;

        // 核心功能：比较和哈希
        virtual bool operator==(const IndexBase& other) const = 0;
        virtual bool operator<(const IndexBase& other) const = 0;
        virtual size_t hash() const = 0;
    };

    template<typename T>
        requires (!std::derived_from<std::remove_cvref_t<T>, IndexBase>)
    class IndexImpl :public IndexBase, public EntryImpl<T>
    {
        using EntryImpl<T>::data;

    public:
        IndexImpl() = delete;
        explicit IndexImpl(const T& value) : EntryImpl<T>(value) {}
        explicit IndexImpl(T&& value) : EntryImpl<T>(std::move(value)) {}
        virtual ~IndexImpl() = default;

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<EntryBase> clone() const override
        {
            return std::make_shared<IndexImpl<T>>(data);
        }

        // 比较和哈希
        virtual bool operator==(const IndexBase& other) const override
        {
            const auto* otherImpl = dynamic_cast<const IndexImpl<T>*>(&other);
            return otherImpl && data == otherImpl->data;
        }
        virtual bool operator<(const IndexBase& other) const override
        {
            const auto* otherImpl = dynamic_cast<const IndexImpl<T>*>(&other);
            return otherImpl && data < otherImpl->data;
        }
        virtual size_t hash() const override
        {
            return std::hash<T>()(data);
        }
    };

    class Index
    {
        std::shared_ptr<EntryBase> pImpl;

    public:
        Index() = delete;
        Index(const Index& other);
        Index(Index&& other);

        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, IndexBase>)
        Index(const T& t)
            : pImpl(std::make_shared<IndexImpl<std::remove_cvref_t<T>>>(t))
        {
        }
        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, IndexBase>)
        Index& operator=(const T& t)
        {
            pImpl = std::make_shared<IndexImpl<std::remove_cvref_t<T>>>(t);
            return *this;
        }

        bool operator==(const Index& other) const;
        bool operator<(const Index& other) const;
        size_t hash() const;


        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, IndexBase>)
        operator T& ()
        {
            if(!pImpl )
                throw Exceptions::Archivist::IndexEmpty();
            auto impl = std::dynamic_pointer_cast<EntryImpl<std::remove_cvref_t<T>>>(pImpl);
            if (!impl)
                throw Exceptions::Archivist::IndexTypeMismatch();
            return impl->operator std::remove_cvref_t<T> & ();
        }

        // 简单输出辅助
        static struct Visualize
        {
            StaticString indexEmpty = "[Empty Index Object]";
            StaticString index = "[Index | {}]";
        } visualize;

        std::string info() const;
    };

}

namespace std
{
    using namespace HYDRA15::Foundation::Archivist;
    template<>
    struct hash<Index>
    {
        size_t operator()(const Index& k) const
        {
            return k.hash();
        }
    };
}