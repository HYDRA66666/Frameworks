#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
    Entry& Entry::list_access(IndexBase key)
    {
        IndexImpl<ListAssist>* index = dynamic_cast<IndexImpl<ListAssist>*>(&key);
        if (!index)
            throw Exceptions::Archivist::IndexTypeMismatch();

        if (ListAssist(*index) >= std::any_cast<ListAssist>(data))
            throw Exceptions::Archivist::EntryElementNotFound();

        return map[key];
    }

    void Entry::list_resize(ListAssist size)
    {
        ListAssist current_size = std::any_cast<ListAssist>(data);

        if (current_size == size)
            return;

        if (current_size < size)
            for(ListAssist i = current_size; i < size; i++)
                map[IndexImpl<ListAssist>(i)] = Entry();
        else
            for(ListAssist i = size; i < current_size; i++)
                map.erase(IndexImpl<ListAssist>(i));

        data = size;
        return;
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
               data = ListAssist(0);
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

   Entry& Entry::operator[](const IndexBase& key)
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
           return std::any_cast<ListAssist>(data);

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
}