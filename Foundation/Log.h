#pragma once
#include "framework.h"
#include "pch.h"

#include "SecretaryException.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::Secretary
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
        static struct Visualize
        {
            StaticString logFormatClr = "\033[0m[ {0} |  Log  ][ {1} ] {2}\033[0m";
            StaticString warningFormatClr = "\033[0m[ {0} |\033[33mWarning\033[0m][ {1} ] {2}\033[0m";
            StaticString errorFormatClr = "\033[0m[ {0} | \033[31mError\033[0m ][ {1} ] {2}\033[0m";
            StaticString debugFormatClr = "\033[0m[ {0} | \033[2mDebug\033[0m ][ {1} ] {2}\033[0m";

            StaticString logFormat = "[ {0} |  Log  ][ {1} ] {2}";
            StaticString warningFormat = "[ {0} |Warning][ {1} ] {2}";
            StaticString errorFormat = "[ {0} | Error ][ {1} ] {2}";
            StaticString debugFormat = "[ {0} | Debug ][ {1} ] {2}";
        };
        
        // 公有接口
    public:
        struct LogStrPkg
        {
            std::string withColor;
            std::string withoutColor;
        };

        static LogStrPkg log(const std::string& title, const std::string& content);
        static LogStrPkg warning(const std::string& title, const std::string& content);
        static LogStrPkg error(const std::string& title, const std::string& content);
        static LogStrPkg debug(const std::string& title, const std::string& content);
    };
}