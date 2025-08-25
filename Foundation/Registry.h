#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"
#include "Entry.h"
#include "Index.h"

namespace HYDRA15::Foundation::Archivist
{
    template<typename L>
    concept lockable = requires(L l) {
        { l.lock() };
        { l.unlock() };
        { l.try_lock() };
    };

    template<typename L>
    concept shared_lockable = requires(L l) {
        { l.lock_shared() };
        { l.unlock_shared() };
        { l.try_lock_shared() };
    };

    template<typename K>
    concept Registry_key = requires(K k) {
        { std::hash<K>()(k) } -> std::same_as<size_t>;
    } && requires(K a, K b) {
        { a == b } -> std::same_as<bool>;
    };

    template<typename K, typename V, typename L>
        requires Registry_key<K> && lockable<L>
    class RegistryBasic
    {
        // 类型定义
    public:
        using Map = std::unordered_map<K, V>;


        // 核心数据
    private:
        L lock;
        Map tab;
        size_t max = 0;

        // 构造与析构
    public:
        RegistryBasic(size_t maxSize = 0)
            :max(maxSize)
        {
            if (max > tab.max_size())
                throw Exceptions::Archivist::RegistryTabletInvalidMaxSize();
        }
        RegistryBasic() = delete;

        // 注册
        void regist(const K& key, V&& value)
        {
            if (max > 0 && tab.size() >= max)
                throw Exceptions::Archivist::RegistryTabletFull();
            if (tab.contains(key))
                throw Exceptions::Archivist::RegistryKeyExists();

            tab[key] = std::forward<V>(value); // 使用拷贝构造
        }
        bool unregist(const K& key)
        {
            return tab.erase(key);
        }
        V& find(const K& key)
        {
            if (!tab.contains(key))
                throw Exceptions::Archivist::RegistryKeyNotFound();
            return tab[key];
        }
    };

    template<typename L>
        requires lockable<L>
    using Registry = RegistryBasic<Index, Entry, L>;
    
    template<typename L>
        requires lockable<L>
    class RegistryInt : public RegistryBasic<unsigned long long, Entry, L>
    {
        // 类型定义
    public:
        using UintIndex = unsigned long long;
        // 核心数据
        UintIndex current = 0;
        UintIndex start = 0;

        // 构造与析构
    public:
        RegistryInt(UintIndex startKey = 0, size_t maxSize = 0)
            : RegistryBasic<UintIndex, Entry, L>(maxSize), start(startKey), current(startKey)
        {
        }

        // 辅助函数
    private:
        UintIndex find_next_key();

        // 注册
    public:
        UintIndex regist(Entry&& value = Entry());
    };
}