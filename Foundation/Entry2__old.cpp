#include "pch.h"
#include "Entry2.h"



namespace HYDRA15::Foundation::Archivist
{
    Entry& Entry::operator[](const Entry& key)
    {
        return std::any_cast<Map&>(data)[key];
    }


}