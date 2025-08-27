#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::Assistant
{
    //将time_t格式的时间戳转化为日期、时间
    std::string to_date_string(time_t stamp);
    std::string to_time_string(time_t stamp);
    std::string to_date_time_string(time_t stamp);

}