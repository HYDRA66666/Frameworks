#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 条目 可以存储任意数据类型，支持移动构造和拷贝构造
    // 使用示例（详细内容见类声明）：
    //  - 注意：请使用 Entry 类创建容器对象
    //  - 构造容器：
    //      - Entry e1 = 42;
    //      - Entry e2(std::string("Hello, World!"));
    //      - Entry e3 = other;
    //      - 注意：不要使用c风格的字符串，因为它们会被当作 const char* 处理。字符串请使用 std::string 或其他字符串容器。
    //  - 获取数据：
    //      - int value = static_cast<int>(e1);
    //      - std::string str& = static_cast<std::string&>(e2);
    //  - 输出信息：
    //      - std::cout << e1.info() << std::endl;
    //      - std::cout << e2 << std::endl;
    //      - 注意：自定义类型需要实现 std::to_string(const T&) 函数以支持数据输出，否则只能输出类型信息。
    // 
    // Entry类声明大致如下：
    //class Entry
    //{
    //    std::shared_ptr<EntryBase> pImpl;

    //    // 构造、析构、复制和数据获取
    //public:
    //    Entry() = default;
    //    ~Entry() = default;

    //    // 从其他 Entry 构造
    //    Entry(const Entry& other);
    //    Entry(Entry&& other);
    //    Entry& operator=(const Entry& other);
    //    Entry& operator=(Entry&& other);

    //    // 从任意数据类型构造
    //    template<typename T>
    //    Entry(const T& value);
    //    template<typename T>
    //    Entry(T&& value)
    //    template<typename T>
    //    Entry& operator=(const T& value);
    //    template<typename T>
    //    Entry& operator=(T&& value);

    //    // 数据访问
    //    template<typename T>
    //    operator T& ();

    //    // 信息输出支持
    //public:
    //    std::string info() const;
    //    std::ostream& operator<<(std::ostream& os) const;
    //};

    /***************************** 基 类 *****************************/
    // 接口定义
    class EntryBase
    {
    public:
        virtual ~EntryBase() = default;

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<EntryBase> clone() const = 0;

        // 信息输出支持
    protected:
        static struct Visualize
        {
            StaticString entryWithKnownType = "type: {}, data: {}";
            StaticString entryWithUnknownType = "unknown type: {}";
        } visualize;

    public:
        virtual std::string info() const = 0;
    };

    // 信息输出相关概念
    template<typename T>
    concept can_be_transfer_to_string = requires(std::remove_cvref_t<T> a) {
        { std::to_string(a) } -> std::convertible_to<std::string>;
    } || requires(std::remove_cvref_t<T> a) {
        { to_string(a) } -> std::convertible_to<std::string>;
    };

    template<class T>
    concept has_info_interface = requires(std::remove_cvref_t<T> a) {
        { a.info() } -> std::convertible_to<std::string>;
    };


    /***************************** 派生类 *****************************/
    // 存储数据
    template<typename T>
        requires (!std::derived_from <std::remove_cvref_t<T> , EntryBase> )
    class EntryImpl : public EntryBase
    {
    protected:
        T data;

    public:
        EntryImpl() = delete;
        explicit EntryImpl(const T& value) : data(value) {}
        explicit EntryImpl(T&& value) : data(std::move(value)) {}
        virtual ~EntryImpl() = default;

        // 数据获取
        operator T& ()
        {
            return data;
        }

        // 类型擦除状态下的拷贝支持
        virtual std::shared_ptr<EntryBase> clone() const override
        {
            return std::make_shared<EntryImpl<T>>(data);
        }


        // 信息输出支持
        virtual std::string info() const override
        {
            if constexpr (std::is_same_v<T, std::string>)
                return std::format(
                    visualize.entryWithKnownType.data(),
                    typeid(T).name(),
                    data
                );
            else if constexpr (can_be_transfer_to_string<T>)
                return std::format(
                    visualize.entryWithKnownType.data(),
                    typeid(T).name(),
                    std::to_string(data)
                );
            else if constexpr (has_info_interface<T>)
                return std::format(
                    visualize.entryWithKnownType.data(),
                    typeid(T).name(),
                    data.info()
                );
            else
                return std::format(
                    visualize.entryWithUnknownType.data(),
                    typeid(T).name()
                );
        }
    };

    /***************************** 主 类 *****************************/
    // 包装，用户接口
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
        operator T& () const
        {
            if (!pImpl)
                throw Exceptions::Archivist::EntryEmpty();

            auto impl = std::dynamic_pointer_cast<EntryImpl<std::remove_cvref_t<T>>>(pImpl);

            if (!impl)
                throw Exceptions::Archivist::EntryTypeMismatch();

            return impl->operator std::remove_cvref_t<T> & ();
        }
        template<typename T>
            requires (!std::derived_from <std::remove_cvref_t<T>, EntryBase>)
        T& get() const
        {
            if (!pImpl)
                throw Exceptions::Archivist::EntryEmpty();
            auto impl = std::dynamic_pointer_cast<EntryImpl<std::remove_cvref_t<T>>>(pImpl);
            if (!impl)
                throw Exceptions::Archivist::EntryTypeMismatch();
            return impl->operator std::remove_cvref_t<T> &();
        }

        // 信息输出支持
    private:
        static struct Visualize
        {
            StaticString emptyEntry = "[Empty Entry object]";
            StaticString entry = "[Entry | {}]";
        } visualize;
    public:
        std::string info() const;
        std::ostream& operator<<(std::ostream& os) const;
    };




    
}