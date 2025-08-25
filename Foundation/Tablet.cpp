#include "pch.h"
#include "Tablet.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry& Tablet::list_access(const Index& key)
    {
        UintIndex k;
        bool converted = false;

        // 尝试解析常规整型
#define TRY(TYPE) \
        try { \
            k = static_cast<UintIndex>(static_cast<TYPE>(key)); \
            converted = true; \
        } catch (Exceptions::Archivist&) { \
        }

        TRY(int);
        TRY(unsigned int);
        TRY(long long);
        TRY(unsigned long long);

#undef TRY

        if (!converted)
            throw Exceptions::Archivist::IndexTypeMismatch();

        if (k >= listSize)
            throw Exceptions::Archivist::TabletListRangeExceed();

        return data[k];
    }

    void Tablet::list_resize(UintIndex size)
    {
        if (size > data.max_size())
            throw Exceptions::Archivist::TabletListBadSize();

        if (listSize == size)
            return;

        if (listSize < size)
            for (UintIndex i = listSize; i < size; i++)
                data[i] = Entry();
        else
            for (UintIndex i = size; i < listSize; i++)
                data.erase(i);

        listSize = size;
        return;
    }

    void Tablet::list_push(Entry&& entry)
    {
        if (listSize >= data.max_size() - 1 || listSize >= std::numeric_limits<UintIndex>::max())
            throw Exceptions::Archivist::TabletContainerFull();

        data[listSize] = std::forward<Entry>(entry);
        listSize++;
    }

    Entry& Tablet::list_front()
    {
        if (listSize == 0)
            throw Exceptions::Archivist::TabletContainerEmpty();
        return data[UintIndex(0)];
    }

    Entry& Tablet::list_back()
    {
        if (listSize == 0)
            throw Exceptions::Archivist::TabletContainerEmpty();
        return data[listSize - 1];
    }

    void Tablet::queue_push(Entry&& entry)
    {
        if (data.size() >= data.max_size() - 1 || queueRange.second == queueRange.first - 1)
            throw Exceptions::Archivist::TabletContainerFull();

        data[queueRange.second] = std::forward<Entry>(entry);
        if (queueRange.second == std::numeric_limits<UintIndex>::max())
            queueRange.second = 0;
        else
            queueRange.second++;
    }

    void Tablet::queue_pop()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::Archivist::TabletContainerEmpty();

        data.erase(Index(queueRange.first));
        if (queueRange.first == std::numeric_limits<UintIndex>::max())
            queueRange.first = 0;
        else
            queueRange.first++;
    }

    Entry& Tablet::queue_front()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::Archivist::TabletContainerEmpty();

        return data[queueRange.first];
    }

    Entry& Tablet::queue_back()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::Archivist::TabletContainerEmpty();

        if (queueRange.second == 0)
            return data[std::numeric_limits<UintIndex>::max()];
        else
            return data[queueRange.second - 1];
    }

    Tablet::Tablet(Type t)
        :type(t)
    {
    }

    Tablet::Map Tablet::get_container() const
    {
        return data;
    }

    Tablet::Map& Tablet::get_container_ref()
    {
        return data;
    }

    Entry& Tablet::operator[](const Index& idx)
    {
        return data[idx];
    }

    void Tablet::push(Entry&& entry)
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return list_push(std::forward<Entry>(entry));

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            return queue_push(std::forward<Entry>(entry));

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    void Tablet::pop()
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            return queue_pop();

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    Entry& Tablet::front()
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return list_front();

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            return queue_front();

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    Entry& Tablet::back()
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return list_back();

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            return queue_back();

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    size_t Tablet::size() const
    {
        return data.size();
    }

    void Tablet::resize(size_t size)
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return list_resize(size);

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    bool Tablet::empty() const
    {
        return data.empty();
    }

    void Tablet::clear()
    {
        data.clear();
        listSize = 0;
        queueRange = { 0, 0 };
    }

    Tablet::Type Tablet::get_type() const
    {
        return type;
    }

    void Tablet::set_type(Type t)
    {
        if (type != t)
        {
            data.clear();
            listSize = 0;
            queueRange = { 0, 0 };
            type = t;
        }
    }

    Tablet::iterator::iterator(Tablet& tab, Tablet::UintIndex idx, Tablet::Map::iterator it)
        :tablet(tab), index(idx), it(it)
    {

    }

    Tablet::iterator& Tablet::iterator::operator++()
    {
        switch (tablet.type)
        {
        case Tablet::Type::map:
            it++;
            return *this;

        case Tablet::Type::list:
            index++;
            if(index>= tablet.listSize)
                it = tablet.data.end();
            else
                it = tablet.data.find(index);
            return *this;
                
        case Tablet::Type::queue:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();
        }
    }

    Tablet::Pair& Tablet::iterator::operator*() const
    {
        return *it;
    }

    bool Tablet::iterator::operator==(const iterator& other) const
    {
        return it == other.it;
    }

    Tablet::iterator Tablet::begin()
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            return Tablet::iterator(*this, 0, data.begin());

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return Tablet::iterator(*this, 0, data.find(UintIndex(0)));

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    Tablet::iterator Tablet::end()
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            return Tablet::iterator(*this, 0, data.end());

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return Tablet::iterator(*this, listSize, data.end());

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            throw Exceptions::Archivist::TabletInvalidContainerOperation();

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }

    std::string Tablet::info() const
    {
        switch (type)
        {
        case HYDRA15::Foundation::Archivist::Tablet::Type::map:
            return std::format(
                visualize.tabletMap.data(),
                data.size()
            );

        case HYDRA15::Foundation::Archivist::Tablet::Type::list:
            return std::format(
                visualize.tabletList.data(),
                data.size()
            );

        case HYDRA15::Foundation::Archivist::Tablet::Type::queue:
            return std::format(
                visualize.tabletQueue.data(),
                data.size()
            );

        default:
            throw Exceptions::Archivist::TabletUnknownExpt();
        }
    }
}

