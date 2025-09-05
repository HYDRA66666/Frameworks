#pragma once
#include "framework.h"
#include "pch.h"

#include "entry.h"
#include "index.h"
#include "archivist_exception.h"

namespace HYDRA15::Foundation::archivist
{
    // 支持存储映射、列表和队列三种数据结构
    // 表项的的索引和元素为 Index 和 Entry 类型，以支持任意类型的索引和元素
    // 三种数据结构均使用 std::unordered_map 作为底层实现
    class tablet
    {
        // 数据类型
    public:
        using map = std::unordered_map<index, entry>;
        using pair = std::pair<const index, entry>;
        using uint_index = size_t;
        enum class type
        {
            map,
            list,
            queue
        };


        // 核心数据
    private:
        type container_type;
        map data;
        uint_index listSize = 0;
        std::pair<uint_index, uint_index> queueRange = { 0, 0 };

        // 辅助函数
    private:
        entry& list_access(const index& key);
        void list_resize(uint_index size);
        void list_push(entry&& item);
        entry& list_front();
        entry& list_back();

        void queue_push(entry&& item);
        void queue_pop();
        entry& queue_front();
        entry& queue_back();


        // 构造与析构
    public:
        tablet() = delete;
        tablet(const tablet&) = default;
        tablet(tablet&&) = default;
        ~tablet() = default;

        // 直接构造为对应类型
        tablet(type t);


        // 访问
    public:
        // 获取容器
        map get_container() const;
        map& get_container_ref();

        // 访问容器数据
        entry& operator[](const index& idx);

        // 增减元素
        void push(entry&& item);
        void pop();
        entry& front();
        entry& back();


        // 修改容器
    public:
        // 大小相关
        size_t size() const;
        void resize(size_t size);

        // 清空与检查
        bool empty() const;
        void clear();

        // 类型
        type get_type() const;
        void set_type(type t);


        // 迭代器
    public:
        // 逻辑：
        //   - 如果Tablet为map类型，直接返回引用map的迭代器
        //   - 如果Entry为list类型，返回一个迭代器，按照索引的顺序遍历map中的元素
        class iterator
        {
            // 核心数据
        private:
            tablet& tab;
            tablet::uint_index index;
            tablet::map::iterator it;

            // 构造
        private:
            iterator() = delete;
            iterator(tablet& tab, tablet::uint_index idx, tablet::map::iterator iter);
            friend class tablet;

            // 迭代器操作
        public:
            iterator& operator++();
            tablet::pair& operator*() const;
            bool operator==(const iterator& other) const;
        };
        friend class iterator;

        iterator begin();
        iterator end();


        // 信息输出支持
    private:
        static struct visualize
        {
            static_string tabletMap = "[Tablet | Type: Map, Size: {}]";
            static_string tabletList = "[Tablet | Type: List, Size: {}]";
            static_string tabletQueue = "[Tablet | Type: Queue, Size: {}]";
        } vslz;

    public:
        std::string info() const;
    };


}

