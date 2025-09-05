#pragma once
#include "framework.h"
#include "pch.h"

#include "archivist_exception.h"
#include "Entry.h"

namespace HYDRA15::Foundation::archivist
{
    // 可以存储任意数据类型的索引
    // 注意：索引的实际类型必须支持比较和哈希
    // 注意：如需比较大小，两个索引必须包含同一类型的数据

    /***************************** 基 类 *****************************/
    // 接口定义
    class index_base
    {
    public:
        virtual ~index_base() = default;

        // 核心功能：比较和哈希
        virtual bool operator==(const index_base& other) const = 0;
        virtual bool operator<(const index_base& other) const = 0;
        virtual size_t hash() const = 0;
    };

    /***************************** 派生类 *****************************/
    // 存储数据，实现核心功能
    template<typename T>
        requires (!std::derived_from<std::remove_cvref_t<T>, index_base>)
    class index_impl :public index_base, public entry_impl<T>
    {
        using entry_impl<T>::data;

    public:
        index_impl() = delete;
        explicit index_impl(const T& value) : entry_impl<T>(value) {}
        explicit index_impl(T&& value) : entry_impl<T>(std::move(value)) {}
        virtual ~index_impl() = default;

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<entry_base> clone() const override
        {
            return std::make_shared<index_impl<T>>(data);
        }

        // 比较和哈希
        virtual bool operator==(const index_base& other) const override
        {
            const auto* otherImpl = dynamic_cast<const index_impl<T>*>(&other);
            return otherImpl && data == otherImpl->data;
        }
        virtual bool operator<(const index_base& other) const override
        {
            const auto* otherImpl = dynamic_cast<const index_impl<T>*>(&other);
            if(!otherImpl)
                throw Exceptions::archivist::IndexTypeMismatch();
            return data < otherImpl->data;
        }
        virtual size_t hash() const override
        {
            return std::hash<T>()(data);
        }
    };

    /***************************** 主 类 *****************************/
    // 包装，用户接口
    class index
    {
        std::shared_ptr<entry_base> pImpl;

    public:
        index() = delete;
        index(const index& other);
        index(index&& other);

        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, index_base>)
        index(const T& t)
            : pImpl(std::make_shared<index_impl<std::remove_cvref_t<T>>>(t))
        {
        }
        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, index_base>)
        index& operator=(const T& t)
        {
            pImpl = std::make_shared<index_impl<std::remove_cvref_t<T>>>(t);
            return *this;
        }

        bool operator==(const index& other) const;
        bool operator<(const index& other) const;
        size_t hash() const;


        template<typename T>
            requires (!std::derived_from<std::remove_cvref_t<T>, index_base>)
        operator T& () const
        {
            if(!pImpl )
                throw Exceptions::archivist::IndexEmpty();
            auto impl = std::dynamic_pointer_cast<entry_impl<std::remove_cvref_t<T>>>(pImpl);
            if (!impl)
                throw Exceptions::archivist::IndexTypeMismatch();
            return impl->operator std::remove_cvref_t<T> & ();
        }

        // 简单输出辅助
        static struct visualize
        {
            static_string indexEmpty = "[Empty Index Object]";
            static_string index = "[Index | {}]";
        } vslz;

        std::string info() const;
    };

}

namespace std
{
    using namespace HYDRA15::Foundation::archivist;
    template<>
    struct hash<index>
    {
        size_t operator()(const index& k) const
        {
            return k.hash();
        }
    };
}