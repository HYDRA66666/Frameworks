#include "pch.h"
#include "tablet.h"

namespace HYDRA15::Foundation::archivist
{
    entry& tablet::list_access(const index& key)
    {
        uint_index k;
        bool converted = false;

        // 尝试解析常规整型
#define TRY(TYPE) \
        try { \
            k = static_cast<uint_index>(static_cast<TYPE>(key)); \
            converted = true; \
        } catch (Exceptions::archivist&) { \
        }

        TRY(int);
        TRY(unsigned int);
        TRY(long long);
        TRY(unsigned long long);

#undef TRY

        if (!converted)
            throw Exceptions::archivist::IndexTypeMismatch();

        if (k >= listSize)
            throw Exceptions::archivist::TabletListRangeExceed();

        return data[k];
    }

    void tablet::list_resize(uint_index size)
    {
        if (size > data.max_size())
            throw Exceptions::archivist::TabletListBadSize();

        if (listSize == size)
            return;

        if (listSize < size)
            for (uint_index i = listSize; i < size; i++)
                data[i] = entry();
        else
            for (uint_index i = size; i < listSize; i++)
                data.erase(i);

        listSize = size;
        return;
    }

    void tablet::list_push(entry&& item)
    {
        if (listSize >= data.max_size() - 1 || listSize >= std::numeric_limits<uint_index>::max())
            throw Exceptions::archivist::TabletContainerFull();

        data[listSize] = std::forward<entry>(item);
        listSize++;
    }

    entry& tablet::list_front()
    {
        if (listSize == 0)
            throw Exceptions::archivist::TabletContainerEmpty();
        return data[uint_index(0)];
    }

    entry& tablet::list_back()
    {
        if (listSize == 0)
            throw Exceptions::archivist::TabletContainerEmpty();
        return data[listSize - 1];
    }

    void tablet::queue_push(entry&& item)
    {
        if (data.size() >= data.max_size() - 1 || queueRange.second == queueRange.first - 1)
            throw Exceptions::archivist::TabletContainerFull();

        data[queueRange.second] = std::forward<entry>(item);
        if (queueRange.second == std::numeric_limits<uint_index>::max())
            queueRange.second = 0;
        else
            queueRange.second++;
    }

    void tablet::queue_pop()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::archivist::TabletContainerEmpty();

        data.erase(index(queueRange.first));
        if (queueRange.first == std::numeric_limits<uint_index>::max())
            queueRange.first = 0;
        else
            queueRange.first++;
    }

    entry& tablet::queue_front()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::archivist::TabletContainerEmpty();

        return data[queueRange.first];
    }

    entry& tablet::queue_back()
    {
        if (queueRange.first == queueRange.second)
            throw Exceptions::archivist::TabletContainerEmpty();

        if (queueRange.second == 0)
            return data[std::numeric_limits<uint_index>::max()];
        else
            return data[queueRange.second - 1];
    }

    tablet::tablet(type t)
        :container_type(t)
    {
    }

    tablet::map tablet::get_container() const
    {
        return data;
    }

    tablet::map& tablet::get_container_ref()
    {
        return data;
    }

    entry& tablet::operator[](const index& idx)
    {
        return data[idx];
    }

    void tablet::push(entry&& item)
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return list_push(std::forward<entry>(item));

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            return queue_push(std::forward<entry>(item));

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    void tablet::pop()
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
        case HYDRA15::Foundation::archivist::tablet::type::list:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            return queue_pop();

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    entry& tablet::front()
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return list_front();

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            return queue_front();

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    entry& tablet::back()
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return list_back();

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            return queue_back();

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    size_t tablet::size() const
    {
        return data.size();
    }

    void tablet::resize(size_t size)
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
        case HYDRA15::Foundation::archivist::tablet::type::queue:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return list_resize(size);

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    bool tablet::empty() const
    {
        return data.empty();
    }

    void tablet::clear()
    {
        data.clear();
        listSize = 0;
        queueRange = { 0, 0 };
    }

    tablet::type tablet::get_type() const
    {
        return container_type;
    }

    void tablet::set_type(type t)
    {
        if (container_type != t)
        {
            data.clear();
            listSize = 0;
            queueRange = { 0, 0 };
            container_type = t;
        }
    }

    tablet::iterator::iterator(tablet& tab, tablet::uint_index idx, tablet::map::iterator it)
        :tab(tab), index(idx), it(it)
    {

    }

    tablet::iterator& tablet::iterator::operator++()
    {
        switch (tab.container_type)
        {
        case tablet::type::map:
            it++;
            return *this;

        case tablet::type::list:
            index++;
            if(index>= tab.listSize)
                it = tab.data.end();
            else
                it = tab.data.find(index);
            return *this;
                
        case tablet::type::queue:
            throw Exceptions::archivist::TabletInvalidContainerOperation();
        }
    }

    tablet::pair& tablet::iterator::operator*() const
    {
        return *it;
    }

    bool tablet::iterator::operator==(const iterator& other) const
    {
        return it == other.it;
    }

    tablet::iterator tablet::begin()
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            return tablet::iterator(*this, 0, data.begin());

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return tablet::iterator(*this, 0, data.find(uint_index(0)));

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    tablet::iterator tablet::end()
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            return tablet::iterator(*this, 0, data.end());

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return tablet::iterator(*this, listSize, data.end());

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            throw Exceptions::archivist::TabletInvalidContainerOperation();

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }

    std::string tablet::info() const
    {
        switch (container_type)
        {
        case HYDRA15::Foundation::archivist::tablet::type::map:
            return std::format(
                vslz.tabletMap.data(),
                data.size()
            );

        case HYDRA15::Foundation::archivist::tablet::type::list:
            return std::format(
                vslz.tabletList.data(),
                data.size()
            );

        case HYDRA15::Foundation::archivist::tablet::type::queue:
            return std::format(
                vslz.tabletQueue.data(),
                data.size()
            );

        default:
            throw Exceptions::archivist::TabletUnknownExpt();
        }
    }
}

