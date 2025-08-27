#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::Secretary
{
    // 提供统一的接口接受日志内容，格式化成字符串，最后输出至 PrintCenter
    class Log
    {
        // 禁止构造
    private:
        Log() = delete;
        Log(const Log&) = delete;
        ~Log() = delete;

        // 私有数据
    private:
        static struct Visualize
        {
            StaticString logFormatClr = "\033[0m[ {0} | {1} ][ Log ] {2}\033[0m";
            StaticString warningFormatClr = "\033[0m[ {0} | {1} ][ \033[3mWarn\033[0m ] {2}\033[0m";
            StaticString errorFormatClr = "\033[0m[ {0} | {1} ][ \033[31mError\033[0m ] {2}\033[0m";
            StaticString debugFormatClr = "\033[0m[ {0} | {1} ][ \033[2mDebug\033[0m ] {2}\033[0m";

            StaticString logFormat = "[ {0} | {1} ][ Log ] {2}";
            StaticString warningFormat = "[ {0} | {1} ][ Warn ] {2}";
            StaticString errorFormat = "[ {0} | {1} ][ Error ] {2}";
            StaticString debugFormat = "[ {0} | {1} ][ Debug ] {2}";
        };

        // 辅助函数
    private:
        static std::string to_date_time_string(const time_t& stamp);
        
        // 公有接口
    public:
        static void log(const std::string& title, const std::string& content);
        static void warning(const std::string& title, const std::string& content);
        static void error(const std::string& title, const std::string& content);
        static void debug(const std::string& title, const std::string& content);
    };
}