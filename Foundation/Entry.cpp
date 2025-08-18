#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry::Entry(std::initializer_list<IntPair> list)
        : type(Type::intMap), data(IntMap(list.begin(), list.end()))
    {
       
    }

    Entry::Entry(std::initializer_list<StringPair> list)
        : type(Type::stringMap), data(StringMap(list.begin(), list.end()))
    {

    }

    Entry::Entry(std::initializer_list<Entry> list)
        : type(Type::dequeList), data(DequeList(list.begin(), list.end()))
    {

    }

    Entry::Entry(IntMap map)
    {
        type = Type::intMap;
        data = map;
    }

    Entry::Entry(StringMap map)
    {
        type = Type::stringMap;
        data = map;
    }

    Entry::Entry(DequeList deque)
    {
        type = Type::dequeList;
        data = deque;
    }

    Entry& Entry::operator[](int key)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();
        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();
        case Type::intMap: [[likely]]
            return std::any_cast<IntMap&>(data)[key];
        case Type::dequeList: [[likely]]
            return std::any_cast<DequeList&>(data)[key];
        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    Entry& Entry::operator[](const std::string& key)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();
        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();
        case Type::stringMap: [[likely]]
            return std::any_cast<StringMap&>(data)[key];
        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    Entry& Entry::operator[](const char* key)
    {
        return operator[](std::string(key));
    }





}
