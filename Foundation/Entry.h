#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 结构化数据的节点，可以储存：
    //   - 任何数据类型，作为终点使用
    //   - 特定容器类型，作为节点使用
    //      - 整数映射（std::unordered_map<long long int, Entry>）
    //      - 字符串映射（std::unordered_map<std::string, Entry>）
    //      - 双端队列（std::deque<Entry>）
    class Entry
    {
        enum class Type
        {
            empty = 0,
            endpoint,
            intMap,
            stringMap,
            dequeList
        }type = Type::empty;

        std::any data;

    public:
        // 使用的数据结构
        using IntPair = std::pair<long long int, Entry>;
        using StringPair = std::pair<std::string, Entry>;
        using IntMap = std::unordered_map<long long int, Entry>;
        using StringMap = std::unordered_map<std::string, Entry>;
        using DequeList = std::deque<Entry>;


        Entry() = default;
        Entry(const Entry& other) = default;

        // 通过初始化列表构造
        Entry(std::initializer_list<IntPair> list);
        Entry(std::initializer_list<StringPair> list);
        explicit Entry(std::initializer_list<Entry> list);

        // 通过容器构造
        Entry(IntMap map);
        Entry(StringMap map);
        Entry(DequeList deque);

        // 通过数据构造
        template<typename T>
        Entry(const T& t);

        // 访问数据
        Entry& operator[](int key);
        Entry& operator[](const std::string& key);
        Entry& operator[](const char* key);
        template<typename T>
        operator T();
    };

    // 模板函数实现
    template<typename T>
    inline Entry::Entry(const T& t)
        :type(Type::endpoint), data(t)
    {

    }

    template<typename T>
    inline Entry::operator T()
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();
        case Type::endpoint: [[likely]]
            break;
        default:
            throw Exceptions::Archivist::EntryDataTypeMismatch();
        }

        try{
            return std::any_cast<T>(data);
        }
        catch (const std::bad_any_cast&) {
            throw Exceptions::Archivist::EntryDataTypeMismatch();
        }
    }





}