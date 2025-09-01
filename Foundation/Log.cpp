#include "pch.h"
#include "Log.h"

namespace HYDRA15::Foundation::Secretary
{
    Log::LogStrPkg Log::log(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                visualize.logFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    visualize.logFormat.data(),
                    Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }

    Log::LogStrPkg Log::warning(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                visualize.warningFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    visualize.warningFormat.data(),
                    Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }

    Log::LogStrPkg Log::error(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                visualize.errorFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
            std::format(
                visualize.errorFormat.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
           )
        };

    }

    Log::LogStrPkg Log::debug(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                visualize.debugFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    visualize.debugFormat.data(),
                    Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }
}
