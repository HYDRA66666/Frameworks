#pragma once
#include "framework.h"
#include "pch.h"

#include "secretary_exception.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::secretary
{
    // 格式化日志字符串
    // 返回格式化后的字符串，用户需要自行处理输出
    class log
    {
        // 禁止构造
    private:
        log() = delete;
        log(const log&) = delete;
        ~log() = delete;

        // 私有数据
    private:
        static struct visualize
        {
            static_string logFormatClr = "\033[0m[ {0} | INFO ][ {1} ] {2}\033[0m";
            static_string warningFormatClr = "\033[0m[ {0} | \033[33mWARN\033[0m ][ {1} ] {2}\033[0m";
            static_string errorFormatClr = "\033[0m[ {0} | \033[35mERROR\033[0m][ {1} ] {2}\033[0m";
            static_string fatalFormatClr = "\033[0m[ {0} | \033[31mFATAL\033[0m][ {1} ] \033[31m{2}\033[0m";
            static_string debugFormatClr = "\033[0m[ {0} | \033[34mDEBUG\033[0m][ {1} ] {2}\033[0m";
            static_string traceFormatClr = "\033[0m[ {0} | \033[2mTRACE\033[0m][ {1} ] {2}\033[0m";

            static_string logFormat = "[ {0} |  INFO ][ {1} ] {2}";
            static_string warningFormat = "[ {0} | WARN ][ {1} ] {2}";
            static_string errorFormat = "[ {0} | ERROR][ {1} ] {2}";
            static_string fatalFormat = "[ {0} | FATAL][ {1} ] {2}";
            static_string debugFormat = "[ {0} | DEBUG][ {1} ] {2}";
            static_string traceFormat = "[ {0} | ERROR][ {1} ] {2}";
        }vslz;
        
        // 公有接口
    public:
        struct logstr_pkg
        {
            std::string withColor;
            std::string withoutColor;
        };

        static logstr_pkg info(const std::string& title, const std::string& content);
        static logstr_pkg warn(const std::string& title, const std::string& content);
        static logstr_pkg error(const std::string& title, const std::string& content);
        static logstr_pkg fatal(const std::string& title, const std::string& content);
        static logstr_pkg debug(const std::string& title, const std::string& content);
        static logstr_pkg trace(const std::string& title, const std::string& content);
    };
}