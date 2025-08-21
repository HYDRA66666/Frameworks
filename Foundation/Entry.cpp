#include "pch.h"
#include "Entry.h"

namespace HYDRA15::Foundation::Archivist
{
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
           

       case Type::list:
           

       case Type::queue:
           throw Exceptions::Archivist::EntryInvalidContainerOperation();

       default:
           throw Exceptions::Archivist::EntryUnknownExpt();

       }
   }


}