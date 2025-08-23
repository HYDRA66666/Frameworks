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
    //      - 映射（std::unordered_map<Index, Entry>）
    //      - 列表（std::deque<Entry>）
    //      - 队列（std::queue<Entry>）
    // 注意：
    //   - c风格的字符串会被当作指针处理，字符串需要使用std::string或其他类似类型
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
        using RealIndex = size_t;   // 实际索引类型
        using Index = Archivist::Index;
        using QueueAssist = std::pair<RealIndex, RealIndex>;  // 存储队列 首项索引 和 尾项索引+1

    public:
        using Map = std::unordered_map<Index, Entry>;
        using Pair = std::pair<const Index, Entry>;
        using ListIndex = RealIndex;


        // 核心数据
    private:
        Type type = Type::empty;
        std::any data;
        Map map;

        // 辅助函数
    private:
        Entry& list_access(const Index& key);
        void list_resize(RealIndex size);
        void list_push(const Entry& entry);
        Entry& list_front();
        Entry& list_back();

        void queue_push(const Entry& entry);
        void queue_pop();
        Entry& queue_front();
        Entry& queue_back();

        // 构造
    public:
        // 基本构造
        Entry() = default;
        Entry(const Entry& other) = default;
        Entry(Entry&& other);
        Entry& operator=(const Entry& other) = default;
        Entry& operator=(Entry&& other) = default;
        virtual ~Entry() = default;

        // 通过任意数据构造，无论数据是否为容器，都将构造为终点
        template<typename T>
        Entry(T&& t);

        // 直接初始化为对应的空类型
        Entry(Type t);


        // 访问
    public:
        // 访问终点数据
        template<typename T>
        operator T&();

        // 直接获取容器数据
        Map get_container() const;

        // 访问容器数据
        Entry& operator[](const Index& key);


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
        // 作用于终点Entry时与Entry的数据相关
        bool empty() const;
        void clear();

        // 类型相关
        Type get_entry_type() const;
        const std::type_info& get_data_type() const;

        // 数据转换
        static ListIndex to_list_index(const Index& key);

        
        // 迭代器
    public:
        // 逻辑：
        //   - 如果Entry为map类型，直接返回引用map的迭代器
        //   - 如果Entry为list类型，返回一个迭代器，按照索引的顺序遍历map中的元素
        class iterator
        {
            // 核心数据
        private:
            Entry& entry;
            Entry::RealIndex index;
            Entry::Map::iterator it;
            bool isMap;

            // 构造
        private:
            iterator(Entry& e, bool isBegin);
            friend class Entry;

            // 迭代器操作
        public:
            iterator& operator++();
            Entry::Pair& operator*() const;
            bool operator==(const iterator& other) const;
        };
        friend class iterator;
        
        iterator begin();
        iterator end();


        // 简单输出辅助
        static struct Visualize
        {
            StaticString empty = "[Empty Entry object]";
            StaticString knownEndpoint = "[Entry Endpoint of type: {}, data: {}]";
            StaticString unknownEndpoint = "[Entry Endpoint of unknown type: {}]";
            StaticString map = "[Entry Map with {} elements]";
            StaticString list = "[Entry List with {} elements]";
            StaticString queue = "[Entry Queue with {} elements]";
        }visualize;

        std::string info() const;
    };

    template<typename T>
    inline Entry::Entry(T&& t)
        : type(Type::endpoint), data(std::forward<T>(t))
    {
    }

    template<typename T>
    inline Entry::operator T&()
    {
        if (type != Type::endpoint)
            throw Exceptions::Archivist::EntryNotEndpoint();

        try{
            return std::any_cast<T&>(data);
        }
        catch (...){
            throw Exceptions::Archivist::EntryDataTypeMismatch();
        }
    }
}