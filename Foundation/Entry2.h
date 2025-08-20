#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 结构化数据的节点，可以储存：
    //   - 任何数据类型，作为终点使用
    //   - 特定容器类型，作为节点使用
    //      - 映射（std::unordered_map<Entry, Entry>）
    //      - 列表（std::deque<Entry>）
    //      - 队列（std::queue<Entry>）
    class Entry
    {
    public:
        enum class Type
        {
            empty = 0,
            endpoint,
            map,
            list,
            queue
        };

        // 核心数据
    private:
        Type type = Type::empty;
        std::any data;
        std::any assistData;

        // 数据类型
    private:
        using Pair = std::pair<Entry, Entry>;
        using ListAssist = size_t;
        using QueueAssist = std::pair<size_t, size_t>; // pair<frontIndex, backIndex>
    public: 
        using Map = std::unordered_map<Entry, Entry>;

        // 构造
    public:
        // 基本构造
        Entry() = default;
        Entry(const Entry& other) = default;
        virtual ~Entry() = default;

        // 通过初始化列表构造，将构造为对应的容器
        Entry(std::initializer_list<Pair> list);
        explicit Entry(std::initializer_list<Entry> list);

        // 通过任意数据构造，无论数据如何，将构造成对应的数据类型
        template<typename T>
        Entry(const T& t);

        // 直接初始化为对应的类型
        Entry(Type t);

        // 访问容器数据
        Entry& operator[](const Entry& key);          // Key类型，支持任意类型的键

        // 容器修改与信息
    public:
        // 大小相关
        size_t size() const;
        void resize(size_t size);

        // 增减元素
        void push(const Entry& entry);
        void pop();
        Entry& front();
        Entry& back();

        // 清空与检查
        bool empty() const;
        void clear();

        // 类型相关
        Type get_entry_type() const;
        const std::type_info& get_data_type() const;

        // 迭代器支持
        Map::iterator begin();
        Map::iterator end();
    };




}