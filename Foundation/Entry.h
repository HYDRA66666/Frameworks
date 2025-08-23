#pragma once
#include "framework.h"
#include "pch.h"

#include "Index.h"
#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    class EntryBase
    {
    public:
        EntryBase() = default;
        virtual ~EntryBase() = default;

        virtual std::string info() = 0;
    };

    template<typename T>
    class EntryImpl : public EntryBase
    {
        T data;

    public:
        EntryImpl() = delete;
        EntryImpl(const T& val);
        EntryImpl(T&& val);
        virtual ~EntryImpl() = default;

        EntryImpl& operator=(const T& val);
        EntryImpl& operator=(T&& val);

        operator T& ();

        virtual std::string info() override;
    };

    class Entry
    {
        std::shared_ptr<EntryBase> pImpl;

    public:
        Entry() = default;
        Entry(const Entry& other);
        Entry(Entry&& other);

        template<typename T>
            requires (!std::derived_from<T, EntryBase>)
        Entry(const T& val);
        template<typename T>
            requires (!std::derived_from<T, EntryBase>)
        Entry(T&& val);

        template<typename T>
            requires std::derived_from<T, EntryBase>
        Entry(const T& impl);
        template<typename T>
            requires std::derived_from<T, EntryBase>
        Entry(T&& impl);
        
        
    };
}