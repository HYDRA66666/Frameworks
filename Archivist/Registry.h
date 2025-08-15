#pragma once
#include "pch.h"
#include "framework.h"

#include "RegiestTablet.h"
#include "RegistryException.h"  

namespace HYDRA15::Frameworks::Archivist
{
    // 注册机模板
    //   - L: 锁类型，默认为 std::mutex，通过锁类型调整读写调度行为
    // 提供三种注册方法：
    //   - 主动注册：用户提供键值对，若键存在则会报错
    //   - 被动注册：用户提供值，注册机返回新键
    //   - 懒惰注册：用户不提供任何内容，注册机返回一个键，并使用空构造创建值
    // 键需满足 可自增、可比较、可哈希
    // 对传入的值默认采用移动构造，不可移动构造时使用拷贝构造，用户也可通过参数标志位指定使用拷贝构造
    // 键和值均存储在注册机内部，如有需要可以将键和值的类型设置为指针类型
    template<typename K, typename V, typename L>
    class Registry
    {
        using Size = RegistryTablet<K, V, L>::Size;

        RegistryTablet<K, V, L> regTab;
        Size maxSize = 0;
        K currentKey = K();
        const K startKey = K();


    public:
        Registry(K start = K(), Size max = 0)
            :maxSize(max), currentKey(start), startKey(start)
        {
            if (max > regTab.max_size())
                throw iExceptions::Registry::TabletInvalidMaxSize();
        }

        Registry() = delete;

        // 注册
        void regist(const K& key, V&& value)
        {
            if(maxSize > 0 && regTab.size() >= maxSize)
                throw iExceptions::Registry::TabletFull();
            if (regTab.contains(key))
                throw iExceptions::Registry::KeyExists();
            regTab[key] = std::move(value);
        }

        K regist(V&& value = V())
        {
            if(maxSize > 0 && regTab.size() >= maxSize)
                throw iExceptions::Registry::TabletFull();
            
            if constexpr (std::is_integral_v<K>) // 如果是整形键，考虑溢出
            {
                while(currentKey!=std::numeric_limits<K>::max() && regTab.contains(currentKey))
                    currentKey++;
                if (currentKey == std::numeric_limits<K>::max() && regTab.contains(currentKey)) // 若达到最大值，则重新扫描整整表，查找是否有空缺位置
                {
                    currentKey = startKey;
                    while (currentKey != std::numeric_limits<K>::max() && regTab.contains(currentKey))
                        currentKey++;
                    if (currentKey == std::numeric_limits<K>::max()) // 找不到空缺位置，则抛出异常
                        throw iExceptions::Registry::KeyOverflow();
                }
            }
            else // 非整形不考虑溢出，自行解决溢出问题
            {
                while(regTab.contains(currentKey))
                    currentKey++;
            }

            regTab[currentKey] = std::move(value);
            return currentKey;
        }

        // 注销
        bool unregist(const K& key)
        {
            return regTab.erase(key);
        }

        // 查找
        V& find(const K& key)
        {
            if (!regTab.contains(key))
                throw iExceptions::Registry::KeyNotFound();
            return regTab[key];
        }


    };
}