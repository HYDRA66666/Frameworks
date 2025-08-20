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

    Entry::Entry(Type t)
    {
        switch (t)
        {
        case Type::intMap: 
            data = IntMap();
            type = t;
            return;

        case Type::stringMap:
            data = StringMap();
            type = t;
            return;

        case Type::dequeList:
            data = DequeList();
            type = t;
            return;

        case Type::queue:
            data = Queue();
            type = t;
            return;

        default: [[unlikely]]
            type = Type::empty;
            return;
        }
    }

    Entry& Entry::operator[](long long int key)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]] // 空节点则创建容器
            data = IntMap();
            type = Type::intMap;
            return std::any_cast<IntMap&>(data)[key];

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::intMap: [[likely]]
            return std::any_cast<IntMap&>(data)[key];

        case Type::dequeList:    // 兼容内容
            if (key < 0 || key >= std::any_cast<DequeList&>(data).size())
                throw Exceptions::Archivist::EntryBadKey();
            return std::any_cast<DequeList&>(data)[key];

        default:
            throw Exceptions::Archivist::EntryKeyTypeMismatch();
        }
    }

    Entry& Entry::operator[](const std::string& key)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]] // 为空则创建容器
            data = StringMap();
            type = Type::stringMap;
            return std::any_cast<StringMap&>(data)[key];

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::stringMap: [[likely]]
            return std::any_cast<StringMap&>(data)[key];

        default:
            throw Exceptions::Archivist::EntryKeyTypeMismatch();
        }
    }

    Entry& Entry::operator[](const Key& key)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            switch (key.type)
            {
            case Key::Type::intKey:
                data = IntMap();
                type = Type::intMap;
                return std::any_cast<IntMap>(data)[std::any_cast<long long int>(key.data)];

            case Key::Type::stringKey:
                data = StringMap();
                type = Type::stringMap;
                return std::any_cast<StringMap>(data)[std::any_cast<std::string>(key.data)];

            case Key::Type::uIntKey:
                data = DequeList(std::any_cast<size_t>(key.data) + 1);
                type = Type::dequeList;
                return std::any_cast<DequeList>(data)[std::any_cast<size_t>(key.data)];

            default:
                throw Exceptions::Archivist::EntryBadKey();
            }

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::intMap:
            if (key.type != Key::Type::intKey)
                throw Exceptions::Archivist::EntryKeyTypeMismatch();
            return std::any_cast<IntMap&>(data)[std::any_cast<long long int>(key.data)];

        case Type::stringMap:
            if (key.type != Key::Type::stringKey)
                throw Exceptions::Archivist::EntryKeyTypeMismatch();
            return std::any_cast<StringMap&>(data)[std::any_cast<std::string>(key.data)];

        case Type::dequeList:
            if (key.type != Key::Type::uIntKey)
                throw Exceptions::Archivist::EntryKeyTypeMismatch();
            if (std::any_cast<size_t>(key.data) >= std::any_cast<DequeList&>(data).size())
                throw Exceptions::Archivist::EntryBadKey();
            return std::any_cast<DequeList&>(data)[std::any_cast<size_t>(key.data)];

        case Type::queue:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();

        default:
            throw Exceptions::Archivist::make_exception(Exceptions::iExptCodes.entry);
        }
    }

    //Entry& Entry::operator[](const char* key)
    //{
    //    return (*this)[std::string(key)];
    //}

    //Entry& Entry::operator[](const Entry& key)
    //{
    //    if (key.type != Type::endpoint)
    //        throw Exceptions::Archivist::EntryKeyTypeMismatch();

    //    switch (type)
    //    {
    //    case Type::empty: [[unlikely]]
    //        throw Exceptions::Archivist::EntryEmpty();

    //    case Type::endpoint:
    //        throw Exceptions::Archivist::EntryNotContainer();

    //    case Type::intMap: [[likely]]
    //        if(key.data.type() != typeid(long long int))
    //            throw Exceptions::Archivist::EntryKeyTypeMismatch();
    //        return std::any_cast<IntMap&>(data)[std::any_cast<long long int>(key.data)];

    //    case Type::stringMap: [[likely]]
    //        if(key.data.type() != typeid(std::string))
    //            throw Exceptions::Archivist::EntryKeyTypeMismatch();
    //        return std::any_cast<StringMap&>(data)[std::any_cast<std::string>(key.data)];

    //    case Type::dequeList: [[likely]]
    //        if (key.data.type() != typeid(size_t))
    //            throw Exceptions::Archivist::EntryKeyTypeMismatch();
    //        if(std::any_cast<size_t>(key.data) >= std::any_cast<DequeList&>(data).size())
    //            throw Exceptions::Archivist::EntryBadKey();
    //        return std::any_cast<DequeList&>(data)[std::any_cast<size_t>(key.data)];

    //    case Type::queue: [[unlikely]]
    //        throw Exceptions::Archivist::EntryInvalidContainerOperation();

    //    default:
    //        throw Exceptions::Archivist::EntryKeyTypeMismatch();
    //    }
    //}

    size_t Entry::size() const
    {
        switch (type)
        {
        case Type::intMap:
            return std::any_cast<IntMap>(data).size();

        case Type::stringMap:
            return std::any_cast<StringMap>(data).size();

        case Type::dequeList:
            return std::any_cast<DequeList>(data).size();

        case Type::queue:
            return std::any_cast<Queue>(data).size();

        default:
            throw Exceptions::Archivist::EntryNotContainer();
        }
    }

    void Entry::resize(size_t size)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]  // 为空则创建容器
            data = DequeList(size);
            type = Type::dequeList;
            return;

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::dequeList: [[likely]]
            std::any_cast<DequeList&>(data).resize(size);
            return;

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    void Entry::push(const Entry& entry)
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]  // 为空则创建容器
            data = DequeList{ entry };
            type = Type::dequeList;
            return;

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::dequeList: [[likely]]
            std::any_cast<DequeList&>(data).push_back(entry);
            return;

        case Type::queue:
            std::any_cast<Queue&>(data).push(entry);
            return;

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    void Entry::pop()
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::queue: [[likely]]
            std::any_cast<Queue&>(data).pop();
            return;

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    Entry& Entry::front()
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::dequeList:   // 兼容内容
            if (std::any_cast<DequeList&>(data).empty())
                throw Exceptions::Archivist::EntryInvalidContainerOperation();
            return std::any_cast<DequeList&>(data).front();

        case Type::queue: [[likely]]
            return std::any_cast<Queue&>(data).front();

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    Entry& Entry::back()
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::dequeList:   // 兼容内容
            if (std::any_cast<DequeList&>(data).empty())
                throw Exceptions::Archivist::EntryInvalidContainerOperation();
            return std::any_cast<DequeList&>(data).back();

        case Type::queue: [[likely]]
            return std::any_cast<Queue&>(data).back();

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    bool Entry::empty() const
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]
            throw Exceptions::Archivist::EntryEmpty();

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::intMap: [[likely]]
            return std::any_cast<IntMap>(data).empty();

        case Type::stringMap: [[likely]]
            return std::any_cast<StringMap>(data).empty();

        case Type::dequeList: [[likely]]
            return std::any_cast<DequeList>(data).empty();

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    void Entry::clear()
    {
        switch (type)
        {
        case Type::empty: [[unlikely]]  // 为空则不做任何操作
            return;

        case Type::endpoint:
            throw Exceptions::Archivist::EntryNotContainer();

        case Type::intMap: [[likely]]
            std::any_cast<IntMap&>(data).clear();
            return;

        case Type::stringMap: [[likely]]
            std::any_cast<StringMap&>(data).clear();
            return;

        case Type::dequeList: [[likely]]
            std::any_cast<DequeList&>(data).clear();
            return;

        default:
            throw Exceptions::Archivist::EntryInvalidContainerOperation();
        }
    }

    Entry::Type Entry::get_entry_type() const
    {
        return type;
    }

    const std::type_info& Entry::get_data_type() const
    {
        return data.type();
    }

    Entry::Key::Key(long long int key)
        : type(Type::intKey), data(key)
    {
    }

    Entry::Key::Key(const std::string& key)
        : type(Type::stringKey), data(key)
    {
    }

    Entry::Key::Key()
        :type(Type::empty), data()
    {
    }

    Entry::Key::Key(size_t key)
        : type(Type::uIntKey), data(key)
    {
    }

   


/****************************************  DEPRECATED  ****************************************
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

    Entry& Entry::operator[](long long int key)
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
            if (key < 0)
                throw Exceptions::Archivist::EntryInvalidContainerOperation();
            if (key >= std::any_cast<DequeList&>(data).size())
                if (key < std::any_cast<DequeList&>(data).max_size() - 1)
                    std::any_cast<DequeList&>(data).resize(key + 1);
                else
                    throw Exceptions::Archivist::EntryInvalidContainerOperation();
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

************************************************************************************************/





}
