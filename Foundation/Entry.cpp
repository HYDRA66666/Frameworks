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
               data = Map();
               return;

           case Type::list:
               type = Type::list;
               data = List();
               assistData = ListAssist(0);
               return;

           case Type::queue:
               type = Type::queue;
               data = Queue();
               assistData = QueueAssist(0, 0);
               return;

           default:
               return;
       }
   }


}