#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::assistant
{
    std::string operator*(std::string str, size_t count);

    std::string& strip(std::string& str);
}