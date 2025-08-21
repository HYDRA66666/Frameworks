#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry& Entry::list_access(const Index& key)
    {
        RealIndex k;
        bool converted = false;

        if (!converted)
        {
            try {
                k = static_cast<RealIndex>(static_cast<int>(key));
                converted = true;
            }
            catch (Exceptions::Archivist& e)
            {
            }
        }
        if(!converted)
        {
            try {
                k = static_cast<RealIndex>(static_cast<unsigned int>(key));
                converted = true;
            }
            catch (Exceptions::Archivist& e)
            {
            }
        }
        if(!converted)
        {
            try {
                k = static_cast<RealIndex>(static_cast<long long>(key));
                converted = true;
            }
            catch (Exceptions::Archivist& e)
            {
            }
        }
        if (!converted)
        {
            try {
                k = static_cast<RealIndex>(static_cast<RealIndex>(key));
                converted = true;
            }
            catch (Exceptions::Archivist& e)
            {
            }
        }

        if(!converted)
            throw Exceptions::Archivist::IndexTypeMismatch();

        if (k >= std::any_cast<RealIndex>(data))
            throw Exceptions::Archivist::EntryElementNotFound();

        return map[k];

        //if (static_cast<RealIndex>(key) >= std::any_cast<RealIndex>(data))
        //    throw Exceptions::Archivist::EntryElementNotFound();

        //return map[key];
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
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

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
       case Type::endpoint:
           throw Exceptions::Archivist::EntryNotContainer();

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
}