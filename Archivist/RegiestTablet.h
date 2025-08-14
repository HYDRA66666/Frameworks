#pragma once
#include "pch.h"
#include "framework.h"

#include "StaffUnion/SharedContainerBase.h"

namespace HYDRA15::Frameworks::Archivist
{
    template<typename L>
    concept SharedLockable = requires(L l) {
        { l.lock_shared() } -> std::same_as<void>;
        { l.unlock_shared() } -> std::same_as<void>;
    };

    // 注册表是线程安全的，由锁的类型决定读写调度行为
    // 对于值，传入时默认采用移动构造，不可移动构造时使用拷贝构造，用户也可通过参数标志位指定使用拷贝构造
    template<typename K, typename V, typename L = std::mutex>
    class RegistryTablet : StaffUnion::Utilities::SharedContainerBase<std::unordered_map<K,V>,L>
    {
    public:
        using Container = std::unordered_map<K, V>;
        using Size = std::unordered_map<K, V>::size_type;

        // 增删改查
        V& operator[](const K& key)
        {
            if constexpr (SharedLockable<L>)
                return this->call_unique(
                    static_cast<V & (Container::*)(const K&)>(&Container::operator[]),
                    key
                );
            else
                return this->call_locked(
                    static_cast<V & (Container::*)(const K&)>(&Container::operator[]),
                    key
                );
        }

        bool contains(const K& key)
        {
            if constexpr (SharedLockable<L>)
                return this->call_shared(
                    static_cast<bool (Container::*)(const K&)>(&Container::contains),
                    key
                );
            else
                return this->call_locked(
                    static_cast<bool (Container::*)(const K&)const>(&Container::contains),
                    key
                );
        }

        bool erase(const K& key)
        {
            if constexpr (SharedLockable<L>)
                return this->call_unique(
                    static_cast<Size (Container::*)(const K&)>(&Container::erase),
                    key
                ) == 1 ? true : false;
            else
                return this->call_locked(
                    static_cast<Size (Container::*)(const K&)>(&Container::erase),
                    key
                ) == 1 ? true : false;
        }

        void clear()
        {
            if constexpr (SharedLockable<L>)
                this->call_unique(
                    static_cast<void (Container::*)()>(&Container::clear)
                );
            else
                this->call_locked(
                    static_cast<void (Container::*)()>(&Container::clear)
                );
        }

        bool empty()
        {
            if constexpr (SharedLockable<L>)
                return this->call_shared(
                    static_cast<bool(Container::*)()const>(&Container::empty)
                );
            else
                return this->call_locked(
                    static_cast<bool(Container::*)()const>(&Container::empty)
                );
        }

        Size size()
        {
            if constexpr (SharedLockable<L>)
                return this->call_shared(
                    static_cast<Size (Container::*)()const>(&Container::size)
                );
            else
                return this->call_locked(
                    static_cast<Size (Container::*)()const>(&Container::size)
                );
        }

        Size max_size()
        {
            return this->call(
                static_cast<Size(Container::*)()const>(&Container::max_size)
            );
          
        }


    };
}