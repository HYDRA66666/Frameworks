#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 可以存储任意索引类型的容器
    // 提供核心功能：判等、比较和哈希，这些功能需要实际类型拥有对应的运算符
    // Index 类可直接作为 map 的索引使用
    // 
    // 为方便查看，Index的声明简要如下：
    //class Index
    //{
    //public:
    //    Index() = delete;
    //    Index(const Index& other) = default;

    //    // 通过 IndexBase 派生类或任意类型构造
    //    template<typename T>
    //        requires std::derived_from<T, IndexBase>
    //    Index(const T& t);
    //    template<typename T>
    //        requires (!std::derived_from<T, IndexBase>)
    //    Index(T t);

    //    bool operator==(const Index& other) const;
    //    bool operator<(const Index& other) const;
    //    bool operator>(const Index& other) const;
    //    size_t hash() const;

    //    // 获取数据
    //    template<typename T>
    //        requires (!std::derived_from<T, IndexBase>)
    //    operator T& ();
    //    template<typename T>
    //        requires (!std::derived_from<T, IndexBase>)
    //    operator const T& () const;
    //};


    class IndexBase
    {
    public:
        IndexBase() = default;
        IndexBase(const IndexBase& other) = default;
        virtual ~IndexBase() = default;

        // 核心功能：判等、比较和哈希
        virtual bool operator==(const IndexBase& other) const;
        virtual bool operator<(const IndexBase& other) const = 0;
        virtual bool operator>(const IndexBase& other) const = 0;
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

        operator T&()
        {
            return data;
        }

        operator const T&() const
        {
            return data;
        }
    };

    class Index
    {
        std::shared_ptr<IndexBase> pidxb;

    public:
        Index() = delete;
        Index(const Index& other);

        template<typename T>
            requires std::derived_from<T, IndexBase>
        Index(const T& t)
            :pidxb(std::make_shared<T>(t))
        {
        }

        template<typename T>
            requires (!std::derived_from<T, IndexBase>)
        Index(T t)
            : pidxb(std::make_shared<IndexImpl<T>>(t))
        {

        }


        bool operator==(const Index& other) const;
        bool operator<(const Index& other) const;
        bool operator>(const Index& other) const;
        size_t hash() const;


        template<typename T>
            requires (!std::derived_from<T, IndexBase>)
        operator T& ()
        {
            std::shared_ptr<IndexImpl<T>> impl = std::dynamic_pointer_cast<IndexImpl<T>>(pidxb);
            if(!impl)
                throw Exceptions::Archivist::IndexTypeMismatch();
            return impl->operator T & ();
        }

        template<typename T>
            requires (!std::derived_from<T, IndexBase>)
        operator const T& () const
        {
            std::shared_ptr<IndexImpl<T>> impl = std::dynamic_pointer_cast<IndexImpl<T>>(pidxb);
            if (!impl)
                throw Exceptions::Archivist::IndexTypeMismatch();
            return impl->operator const T & ();
        }
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