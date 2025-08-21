#pragma once
#include "framework.h"
#include "pch.h"

#include "Index.h"
#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 结构化数据的节点，可以储存：
    //   - 任何数据类型，作为终点使用
    //   - 特定容器类型，作为节点使用
    //      - 映射（std::unordered_map<IndexBase, Entry>）
    //      - 列表（std::deque<Entry>）
    //      - 队列（std::queue<Entry>）
    class Entry
    {
        // 类型定义
    public:
        enum class Type
        {
            empty = 0,
            endpoint,
            map,
            list,
            queue
        };

    private:
        using Pair = std::pair<std::unique_ptr<IndexBase>, Entry>;
        using ListAssist = size_t; // 存储列表的大小
        using QueueAssist = std::pair<size_t, size_t>; // 存储队列的前后索引

    public:
        using Map = std::unordered_map<std::unique_ptr<IndexBase>, Entry>;
        using List = std::deque<Entry>;
        using Queue = std::queue<Entry>;


        // 核心数据
    private:
        Type type = Type::empty;
        std::any data;
        std::any assistData;


        // 构造
    public:
        // 基本构造
        Entry() = default;
        Entry(const Entry& other) = default;
        virtual ~Entry() = default;

        // 通过任意数据构造，无论数据是否为容器，都将构造为终点
        template<typename T>
        Entry(const T& t);

        // 通过初始化列表构造
        explicit Entry(std::initializer_list<Pair> list);
        explicit Entry(std::initializer_list<Entry> list);

        // 直接初始化为对应的空类型
        Entry(Type t);


        // 访问
    public:
        // 访问终点数据
        template<typename T>
        operator T();

        // 访问容器数据
        Entry& operator[](const IndexBase& key); // Key类型，支持任意类型的键


        // 修改容器
    public:

    };


    // 模板函数实现
    template<typename T>
    Entry::Entry(const T& t)
        : type(Type::endpoint), data(t)
    {
        
    }
}