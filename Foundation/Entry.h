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
        using QueueAssist = std::pair<size_t, size_t>;  // 存储队列 首项索引 和 尾项索引+1
        using RealIndex = size_t;   // 实际索引类型

    public:
        using Map = std::unordered_map<IndexBase, Entry>;
        using Index = IndexImpl<RealIndex>;


        // 核心数据
    private:
        Type type = Type::empty;
        std::any data;
        Map map;

        // 辅助函数
    private:
        Entry& list_access(const IndexBase& key);
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
        virtual ~Entry() = default;

        // 通过任意数据构造，无论数据是否为容器，都将构造为终点
        template<typename T>
        Entry(const T& t);

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
        Entry& operator[](RealIndex key);
        Entry& operator[](const IndexBase& key); // Key类型，支持任意类型的键


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

    };


    // 模板函数实现
    template<typename T>
    Entry::Entry(const T& t)
        : type(Type::endpoint), data(t)
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