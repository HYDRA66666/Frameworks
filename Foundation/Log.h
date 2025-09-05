#pragma once
#include "framework.h"
#include "pch.h"

#include "secretary_exception.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::secretary
{
    // 格式化日志字符串
    // 返回格式化后的字符串，用户需要自行处理输出
    class Log
    {
        // 禁止构造
    private:
        Log() = delete;
        Log(const Log&) = delete;
        ~Log() = delete;

        // 私有数据
    private:
        static struct visualize
        {
            static_string logFormatClr = "\033[0m[ {0} |  Log  ][ {1} ] {2}\033[0m";
            static_string warningFormatClr = "\033[0m[ {0} |\033[33mWarning\033[0m][ {1} ] {2}\033[0m";
            static_string errorFormatClr = "\033[0m[ {0} | \033[31mError\033[0m ][ {1} ] {2}\033[0m";
            static_string debugFormatClr = "\033[0m[ {0} | \033[2mDebug\033[0m ][ {1} ] {2}\033[0m";

            static_string logFormat = "[ {0} |  Log  ][ {1} ] {2}";
            static_string warningFormat = "[ {0} |Warning][ {1} ] {2}";
            static_string errorFormat = "[ {0} | Error ][ {1} ] {2}";
            static_string debugFormat = "[ {0} | Debug ][ {1} ] {2}";
        }vslz;
        
        // 公有接口
    public:
        struct logstr_pkg
        {
            std::string withColor;
            std::string withoutColor;
        };

        static logstr_pkg log(const std::string& title, const std::string& content);
        static logstr_pkg warning(const std::string& title, const std::string& content);
        static logstr_pkg error(const std::string& title, const std::string& content);
        static logstr_pkg debug(const std::string& title, const std::string& content);
    };
}