#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"
#include "Entry.h"
#include "Index.h"

namespace HYDRA15::Foundation::Archivist
{
    // 处理注册相关逻辑
    // 模板参数 K : 键类型，要求满足哈希键约束
    // 模板参数 V : 值类型，不做要求
    // 模板参数 L : 锁类型，如果支持共享锁，则在查询时使用共享锁
    // 如果不需要上锁，可以使用 NotALock 作为锁类型，其满足锁约束，但不会进行任何实际操作

    /***************************** 概 念 *****************************/
    // 锁约束
    template<typename L>
    concept lockable = requires(L l) {
        { l.lock() };
        { l.unlock() };
        { l.try_lock() };
    };

    // 共享锁约束
    template<typename L>
    concept shared_lockable = requires(L l) {
        { l.lock_shared() };
        { l.unlock_shared() };
        { l.try_lock_shared() };
    };

    // 哈希键约束
    template<typename K>
    concept hash_key = requires(K k) {
        { std::hash<K>()(k) } -> std::same_as<size_t>;
    } && requires(K a, K b) {
        { a == b } -> std::same_as<bool>;
    };


    /***************************** 基 类 *****************************/
    // 基础注册机模板，支持任意类型的键和值
    template<typename K, typename V, typename L>
        requires hash_key<K> && lockable<L>
    class RegistryBase
    {
        // 类型定义
    public:
        using RegTab = std::unordered_map<K, V>;


        // 核心数据
    protected:
        mutable L lock; 
        RegTab tab;
        size_t max = 0;

        // 构造与析构
    public:
        RegistryBase(size_t maxSize)
            :max(maxSize)
        {
            if (max > tab.max_size())
                throw Exceptions::Archivist::RegistryTabletInvalidMaxSize();
        }
        RegistryBase() : max(0) {}

        // 注册
        void regist(const K& key, V&& value)
        {
            std::unique_lock lck(lock);

            if (max > 0 && tab.size() >= max)
                throw Exceptions::Archivist::RegistryTabletFull();
            if(tab.size() >= tab.max_size())
                throw Exceptions::Archivist::RegistryTabletFull();
            if (tab.contains(key))
                throw Exceptions::Archivist::RegistryKeyExists();

            tab[key] = std::forward<V>(value); // 使用拷贝构造
        }
        bool unregist(const K& key)
        {
            std::unique_lock lck(lock);

            return tab.erase(key);
        }
        V& find(const K& key)
        {
            if constexpr (shared_lockable<L>)
                std::shared_lock lck(lock);
            else
                std::unique_lock lck(lock);

            if (!tab.contains(key))
                throw Exceptions::Archivist::RegistryKeyNotFound();
            return tab[key];
        }

        // 查询
        bool contains(const K& key) const
        {
            if constexpr (shared_lockable<L>)
                std::shared_lock lck(lock);
            else
                std::unique_lock lck(lock);

            return tab.contains(key);
        }
        size_t size() const
        {
            if constexpr (shared_lockable<L>)
                std::shared_lock lck(lock);
            else
                std::unique_lock lck(lock);

            return tab.size();
        }

    };


    /***************************** 特化类 *****************************/
    // 简单注册机
    using Registry = RegistryBase<Index, Entry, std::mutex>;
    
    // 整数键注册机，支持被动注册和懒注册
    template<typename V, typename L>
        requires lockable<L>
    class RegistryInt : public RegistryBase<unsigned long long, V, L>
    {
        // 类型定义
    public:
        using UintIndex = unsigned long long;
        // 核心数据
        UintIndex current = 0;
        UintIndex start = 0;
        using RegistryBase<UintIndex, V, L>::tab;
        using RegistryBase<UintIndex, V, L>::max;
        using RegistryBase<UintIndex, V, L>::lock;

        // 构造与析构
    public:
        RegistryInt(UintIndex startKey = 0, size_t maxSize = 0)
            : RegistryBase<UintIndex, V, L>(maxSize), start(startKey), current(startKey)
        {
        }

        // 辅助函数
    private:
        void find_next_key()
        {
            if (current != std::numeric_limits<UintIndex>::max())
                current++;   // 默认currentKey已使用
            while (current != std::numeric_limits<UintIndex>::max() && tab.contains(current))
                current++;
            if (current == std::numeric_limits<UintIndex>::max() && tab.contains(current)) // 若达到最大值，则重新扫描整整表，查找是否有空缺位置
            {
                current = start;
                while (current != std::numeric_limits<UintIndex>::max() && tab.contains(current))
                    current++;
                if (current == std::numeric_limits<UintIndex>::max()) // 找不到空缺位置，则抛出异常
                    throw Exceptions::Archivist::RegistryTabletFull();
            }
        }

        // 注册
    public:
        // 被动注册：传入值，注册机分配键
        // 懒注册：不传入值，注册机分配键和默认值
        UintIndex regist(V&& value = V())
        {
            std::unique_lock lck(lock);
            if (max > 0 && tab.size() >= max)
                throw Exceptions::Archivist::RegistryTabletFull();
            if (tab.size() >= tab.max_size())
                throw Exceptions::Archivist::RegistryTabletFull();
            find_next_key();

            tab[current] = std::forward<V>(value);
            return current;
        }
    };

    class NotALock
    {
    public:
        void lock();
        void unlock();
        bool try_lock();
    };
}