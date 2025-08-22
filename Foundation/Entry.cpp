#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry& Entry::list_access(const Index& key)
    {
        RealIndex k;
        bool converted = false;

        // 尝试解析常规整型
#define TRY(Type) \
        try { \
            k = static_cast<RealIndex>(static_cast<Type>(key)); \
            converted = true; \
        } catch (Exceptions::Archivist&) { \
        }

        TRY(int);
        TRY(unsigned int);
        TRY(long long);
        TRY(unsigned long long);

#undef TRY

        if(!converted)
            throw Exceptions::Archivist::IndexTypeMismatch();

        if (k >= std::any_cast<RealIndex>(data))
            throw Exceptions::Archivist::EntryElementNotFound();

        return map[k];

    }

    void Entry::list_resize(RealIndex size)
    {
        RealIndex current_size = std::any_cast<RealIndex>(data);

        if(size> map.max_size())
            throw Exceptions::Archivist::EntryInvalidContainerSize();

        if (current_size == size)
            return;

        if (current_size < size)
            for(RealIndex i = current_size; i < size; i++)
                map[Index(i)] = Entry();
        else
            for(RealIndex i = size; i < current_size; i++)
                map.erase(Index(i));

        data = size;
        return;
    }

    void Entry::list_push(const Entry& entry)
    {
        if (std::any_cast<RealIndex>(data) >= map.max_size() - 1 || std::any_cast<RealIndex>(data) >= std::numeric_limits<RealIndex>::max())
            throw Exceptions::Archivist::EntryContainerFull();

        map[Index(std::any_cast<RealIndex>(data))] = entry;
        data = std::any_cast<RealIndex>(data) + 1;
    }

    Entry& Entry::list_front()
    {
        if(std::any_cast<RealIndex>(data) == 0)
            throw Exceptions::Archivist::EntryContainerEmpty();
        return map[Index(RealIndex(0))];
    }

    Entry& Entry::list_back()
    {
        if(std::any_cast<RealIndex>(data) == 0)
            throw Exceptions::Archivist::EntryContainerEmpty();
        return map[Index(std::any_cast<RealIndex>(data) - 1)];
    }

    void Entry::queue_push(const Entry& entry)
    {
        auto& assist = std::any_cast<QueueAssist&>(data);
        
        if (map.size() >= map.max_size() - 1 || assist.second == assist.first - 1)
            throw Exceptions::Archivist::EntryContainerFull();

        map[Index(assist.second)] = entry;
        if(assist.second==std::numeric_limits<RealIndex>::max())
            assist.second = 0;
        else
            assist.second++;
    }

    void Entry::queue_pop()
    {
        auto& assist = std::any_cast<QueueAssist&>(data);
        
        if (assist.first == assist.second)
            throw Exceptions::Archivist::EntryContainerEmpty();

        map.erase(Index(assist.first));
        if (assist.first == std::numeric_limits<RealIndex>::max())
            assist.first = 0;
        else
            assist.first++;
    }

    Entry& Entry::queue_front()
    {
        auto& assist = std::any_cast<QueueAssist&>(data);

        if( assist.first == assist.second)
            throw Exceptions::Archivist::EntryContainerEmpty();

        return map[Index(assist.first)];
    }

    Entry& Entry::queue_back()
    {
        auto& assist = std::any_cast<QueueAssist&>(data);

        if (assist.first == assist.second)
            throw Exceptions::Archivist::EntryContainerEmpty();

        if (assist.second == 0)
            return map[Index(std::numeric_limits<RealIndex>::max())];
        else
            return map[Index(assist.second - 1)];
    }

    Entry::Entry(Entry&& other)
        : type(other.type), data(std::move(other.data)), map(std::move(other.map))
    {
        other.type = Type::empty;
    }

    Entry::Entry(Type t)
   {
       switch (t)
       {
           case Type::map:
               type = Type::map;
               return;

           case Type::list:
               type = Type::list;
               data = RealIndex(0);
               return;

           case Type::queue:
               type = Type::queue;
               data = QueueAssist(0, 0);
               return;

           default:
               return;
       }
   }

   Entry::Map Entry::get_container() const
   {
       return map;
   }

   Entry& Entry::operator[](const Index& key)
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::map:
           return map[key];
           
       case Type::list:
           return list_access(key);

       case Type::queue:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();

       }
   }

   size_t Entry::size() const
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::map:
           return map.size();

       case Type::list:
           return std::any_cast<RealIndex>(data);

       case Type::queue:
           return std::any_cast<QueueAssist>(data).second - std::any_cast<QueueAssist>(data).first;

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();
       }
   }

   void Entry::resize(size_t size)
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::list:
           list_resize(size);
           return;

       default:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();
       }
   }

   void Entry::push(const Entry& entry)
   {
         switch (type)
         {
         case Type::empty:
         case Type::endpoint:
              throw Exceptions::Archivist::EntryNotContainer();
    
         case Type::list:
              list_push(entry);
              return;
    
         case Type::queue:
              queue_push(entry);
              return;
    
         default:
              throw Exceptions::Archivist::EntryInvalidContainerOperation();
         }
   }

   void Entry::pop()
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::queue:
           queue_pop();
           return;

       default:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();
       }
   }

   Entry& Entry::front()
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::list:
           return list_front();

       case Type::queue:
           return queue_front();

       default:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();
       }
   }

   Entry& Entry::back()
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::list:
           return list_back();

       case Type::queue:
           return queue_back();

       default:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();
       }
   }

   bool Entry::empty() const
   {
       switch (type)
       {
       case Type::empty:
           return true;

       case Type::endpoint:
           return false;

       case Type::map:
       case Type::list:
       case Type::queue:
           return map.empty();

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();
       }
   }

   void Entry::clear()
   {
       switch (type)
       {
       case Type::empty:
           return;

       case Type::endpoint:
           type = Type::empty;
           data = std::any();

       case Type::map:
           map.clear();
           return;

       case Type::list:
           map.clear();
           data = RealIndex(0);
           return;

       case Type::queue:
           map.clear();
           data = QueueAssist(0, 0);
           return;

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();
       }
   }

   Entry::Type Entry::get_entry_type() const
   {
       return type;
   }

   const std::type_info& Entry::get_data_type() const
   {
       if(type!= Type::endpoint)
           throw Exceptions::Archivist::EntryNotEndpoint();

       return data.type();
   }
   Entry::ListIndex Entry::to_list_index(const Index& key)
   {
       return static_cast<ListIndex>(key);
   }

   Entry::iterator::iterator(Entry& e, bool isBegin)
       : entry(e), index(0), isMap(e.type == Type::map)
   {
       if(!isBegin)
       {
           it = entry.map.end();
           return;
       }

       if (isMap)
           it = entry.map.begin();
       else
           it = entry.map.find(Index(index));
   }

   Entry::iterator& Entry::iterator::operator++()
   {
       if (isMap)
           it++;
       else
       {
           index++;
           it = entry.map.find(Index(index));
       }
       return *this;
   }

   Entry::Pair& Entry::iterator::operator*() const
   {
       return *it;
   }

   bool Entry::iterator::operator==(const iterator& other) const
   {
       return it == other.it;
   }

   Entry::iterator Entry::begin()
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       case Type::queue:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();

       default:
           break;
       }

       return Entry::iterator(*this, true);
   }

   Entry::iterator Entry::end()
   {
       switch (type)
       {
       case Type::empty:
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

       default:
           break;
       }

       return Entry::iterator(*this, false);
   }

   std::string Entry::info() const
   {
       switch (type)
       {
       case Type::empty:
           return std::format(visualize.empty);

       case Type::endpoint:
           // 尝试识别常见类型
#define TRY(Type) \
           try { \
               auto v = std::any_cast<Type>(data); \
               return std::format(visualize.knownEndpoint, typeid(Type).name(), v); \
           } catch (std::bad_any_cast&) { \
           }

           TRY(int);
           TRY(unsigned int);
           TRY(long long);
           TRY(unsigned long long);
           TRY(float);
           TRY(double);
           TRY(char);
           TRY(unsigned char);
           TRY(bool);
           TRY(std::string);

#undef TRY

           return std::format(visualize.unknownEndpoint, data.type().name());

       case Type::map:
           return std::format(visualize.map, map.size());

       case Type::list:
           return std::format(visualize.list, map.size());

       case Type::queue:
           return std::format(visualize.queue, map.size());

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();
       }
   }
}