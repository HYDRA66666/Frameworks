#pragma once
#include "framework.h"
#include "pch.h"

#include "AssistantException.h"

namespace HYDRA15::Foundation::Assistant
{
    // 存储时间、提供时间和日期的格式化输出
    // 仅用于日期和时间的输出，不用于精确计时
    extern int localTimeZone; // 本地时区，默认为东八区
    class DateTime
    {
        // 记录的时间
        time_t stamp;

        // 构造和析构
    public:
        DateTime();
        DateTime(time_t t);
        DateTime(const DateTime&) = default;
        DateTime& operator=(const DateTime&) = default;
        ~DateTime() = default;

        // 输出
    public:
        std::string date_time(std::string format = "%Y-%m-%d %H:%M:%S", int timeZone = localTimeZone) const;

        // 静态工具函数
    public:
        static DateTime now();
        static std::string now_date_time(std::string format = "%Y-%m-%d %H:%M:%S", int timeZone = localTimeZone);
    };
}