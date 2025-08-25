#pragma once
#include "framework.h"
#include "pch.h"

#include "Entry.h"
#include "Index.h"
#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // 支持存储映射、列表和队列三种数据结构
    // 表项的的索引和元素为 Index 和 Entry 类型，以支持任意类型的索引和元素
    // 三种数据结构均使用 std::unordered_map 作为底层实现
    class Tablet
    {
        // 数据类型
    public:
        using Map = std::unordered_map<Index, Entry>;
        using Pair = std::pair<const Index, Entry>;
        using UintIndex = size_t;
        enum class Type
        {
            map,
            list,
            queue
        };


        // 核心数据
    private:
        Type type;
        Map data;
        UintIndex listSize = 0;
        std::pair<UintIndex, UintIndex> queueRange = { 0, 0 };

        // 辅助函数
    private:
        Entry& list_access(const Index& key);
        void list_resize(UintIndex size);
        void list_push(const Entry& entry);
        Entry& list_front();
        Entry& list_back();

        void queue_push(const Entry& entry);
        void queue_pop();
        Entry& queue_front();
        Entry& queue_back();


        // 构造与析构
    public:
        Tablet() = delete;
        Tablet(const Tablet&) = default;
        Tablet(Tablet&&) = default;
        ~Tablet() = default;

        // 直接构造为对应类型
        Tablet(Type t);


        // 访问
    public:
        // 获取容器
        Map get_container() const;
        Map& get_container_ref();

        // 访问容器数据
        Entry& operator[](const Index& idx);

        // 增减元素
        void push(const Entry& entry);
        void pop();
        Entry& front();
        Entry& back();


        // 修改容器
    public:
        // 大小相关
        size_t size() const;
        void resize(size_t size);

        // 清空与检查
        bool empty() const;
        void clear();

        // 类型
        Type get_type() const;


        // 迭代器
    public:
        // 逻辑：
        //   - 如果Tablet为map类型，直接返回引用map的迭代器
        //   - 如果Entry为list类型，返回一个迭代器，按照索引的顺序遍历map中的元素
        class iterator
        {
            // 核心数据
        private:
            Tablet& tablet;
            Tablet::UintIndex index;
            Tablet::Map::iterator it;

            // 构造
        private:
            iterator(Entry& e, bool isBegin);
            friend class Entry;

            // 迭代器操作
        public:
            iterator& operator++();
            Tablet::Pair& operator*() const;
            bool operator==(const iterator& other) const;
        };
        friend class iterator;

        iterator begin();
        iterator end();
    };
}