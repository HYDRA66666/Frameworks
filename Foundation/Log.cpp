#include "pch.h"
#include "Log.h"

namespace HYDRA15::Foundation::secretary
{
    Log::logstr_pkg Log::log(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.logFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    vslz.logFormat.data(),
                    assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }

    Log::logstr_pkg Log::warning(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.warningFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    vslz.warningFormat.data(),
                    assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }

    Log::logstr_pkg Log::error(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.errorFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
            std::format(
                vslz.errorFormat.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
           )
        };

    }

    Log::logstr_pkg Log::debug(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.debugFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    vslz.debugFormat.data(),
                    assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }
}
