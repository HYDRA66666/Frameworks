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

    void Tablet::list_push(const Entry& entry)
    {
        if (listSize >= data.max_size() - 1 || listSize >= std::numeric_limits<UintIndex>::max())
            throw 

        data[listSize] = entry;
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

    void Tablet::queue_push(const Entry& entry)
    {
        if (data.size() >= data.max_size() - 1 || queueRange.second == queueRange.first - 1)
            throw 

        data[queueRange.second] = entry;
        if (queueRange.second == std::numeric_limits<UintIndex>::max())
            queueRange.second = 0;
        else
            queueRange.second++;
    }

    void Tablet::queue_pop()
    {
        if (queueRange.first == queueRange.second)
            throw 

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
}
