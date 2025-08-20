#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::Archivist
{
    class AnyKey
    {
        enum class Type :unsigned int
        {
            empty = 0,
            int32,
            int64,
            int128,
            float64,
            stdstring,
            custom = 0xFFFFFFFF
        }type = Type::empty;
        std::any data;

    public:
        AnyKey() = default;
        AnyKey(const AnyKey& other) = default;
        virtual ~AnyKey() = default;

        // 通过任意数据构造
        template<typename T>
        AnyKey(T d);

        bool operator==(const AnyKey& other) const;
    };
}