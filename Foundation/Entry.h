#pragma once
#include "framework.h"
#include "pch.h"

#include "Index.h"
#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 信息输出相关
    static struct Visualize
    {
        StaticString entryWithKnownType = "[Entry object of type: {}, data: {}]";
        StaticString entryWithUnknownType = "Entry object of unknown type: {}]";
        StaticString emptyEntry = "[Empty Entry object]";
    } visualize;

    template<typename T>
    concept is_formattable = requires(T a) {
        { std::to_string(a) } -> std::convertible_to<std::string>;
    };

    template<typename T>
        requires (!is_formattable<T>)
    std::string entry_to_string(const T&)
    {
        return std::format(
            visualize.entryWithUnknownType.data(),
            typeid(T).name()
        );
    }

    template<typename T>
        requires is_formattable<T>
    std::string entry_to_string(const T& data)
    {
        if constexpr (std::is_same_v<T, std::string>)
            return std::format(
                visualize.entryWithKnownType.data(),
                typeid(T).name(),
                data
            );
        else
            return std::format(
                visualize.entryWithKnownType.data(),
                typeid(T).name(),
                std::to_string(data)
            );
    }


    class EntryBase
    {
    public:
        virtual ~EntryBase() = default;

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<EntryBase> clone() const = 0;


        // 信息输出支持
    public:
        virtual std::string info() const = 0;
    };

    template<typename T>
        requires (!std::derived_from <std::remove_cvref_t<T> , EntryBase> )
    class EntryImpl : public EntryBase
    {
        T data;

        friend class Entry;
    public:
        EntryImpl() = delete;
        explicit EntryImpl(const T& value) : data(value) {}
        explicit EntryImpl(T&& value) : data(std::move(value)) {}
        virtual ~EntryImpl() = default;

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<EntryBase> clone() const override
        {
            return std::make_shared<EntryImpl<T>>(data);
        }


        // 信息输出支持
        virtual std::string info() const override
        {
            return entry_to_string<T>(data);
        }
    };

    class Entry
    {
        std::shared_ptr<EntryBase> pImpl;

        // 构造、析构、复制和数据获取
    public:
        Entry() = default;
        ~Entry() = default;

        // 从其他 Entry 构造
        Entry(const Entry& other);
        Entry(Entry&& other);
        Entry& operator=(const Entry& other);
        Entry& operator=(Entry&& other);

        // 从任意数据类型构造
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>) && (!std::is_same_v<std::remove_cvref_t<T>, Entry>)
        Entry(const T& value) : pImpl(std::make_shared<EntryImpl<std::remove_cvref_t<T>>>(value)) {}
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>) && (!std::is_same_v<std::remove_cvref_t<T>, Entry>)
        Entry(T&& value) : pImpl(std::make_shared<EntryImpl<std::remove_cvref_t<T>>>(std::move(value))) {}
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>) && (!std::is_same_v<std::remove_cvref_t<T>, Entry>)
        Entry& operator=(const T& value)
        {
            pImpl = std::make_shared<EntryImpl<std::remove_cvref_t<T>>>(value);
            return *this;
        }
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>) && (!std::is_same_v<std::remove_cvref_t<T>, Entry>)
        Entry& operator=(T&& value)
        {
            pImpl = std::make_shared<EntryImpl<std::remove_cvref_t<T>>>(std::move(value));
            return *this;
        }

        // 数据访问
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>)
        operator T& ()
        {
            if (!pImpl)
                throw Exceptions::Archivist::EntryEmpty();

            auto derived = std::dynamic_pointer_cast<EntryImpl<std::remove_cvref_t<T>>>(pImpl);

            if (!derived)
                throw Exceptions::Archivist::EntryTypeMismatch();

            return derived->data;
        }

        // 信息输出支持
    private:
        StaticString infoEmpty = "[Empty Entry object]";
    public:
        std::string info() const;
        std::ostream& operator<<(std::ostream& os) const;
    };
}