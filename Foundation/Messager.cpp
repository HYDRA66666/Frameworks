#include "pch.h"
#include "Messager.h"

namespace HYDRA15::Foundation::expressman
{
    Messager& Messager::get_instance()
    {
        static Messager instance;
        return instance;
    }
}