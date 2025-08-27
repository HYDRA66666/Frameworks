#include "pch.h"
#include "to_string.h"

namespace HYDRA15::Foundation::Assistant
{
    //将time_t格式的时间戳转化为日期、时间
    std::string to_date_string(time_t stamp)
    {
        tm local;
        localtime_s(&local, &stamp);
        std::string mon = std::to_string(local.tm_mon + 1), day = std::to_string(local.tm_mday);
        if (mon.size() < 2)mon = "0" + mon;
        if (day.size() < 2)day = "0" + day;
        return std::to_string(local.tm_year + 1900) + "-" + mon + "-" + day;
    }

    std::string to_time_string(time_t stamp)
    {
        tm local;
        localtime_s(&local, &stamp);
        std::string hour = std::to_string(local.tm_hour), min = std::to_string(local.tm_min), sec = std::to_string(local.tm_sec);
        if (hour.size() < 2)hour = "0" + hour;
        if (min.size() < 2)min = "0" + min;
        if (sec.size() < 2)sec = "0" + sec;
        return hour + ":" + min + ":" + sec;
    }

    std::string to_date_time_string(time_t stamp)
    {
        return to_date_string(stamp) + " " + to_time_string(stamp);
    }

}