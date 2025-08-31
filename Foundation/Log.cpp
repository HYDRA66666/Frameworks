#include "pch.h"
#include "Log.h"

namespace HYDRA15::Foundation::Secretary
{
    Log::LogStrPkg Log::log(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                Visualize::logFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    Visualize::logFormat.data(),
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
                Visualize::warningFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    Visualize::warningFormat.data(),
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
                Visualize::errorFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
            std::format(
                Visualize::errorFormat.data(),
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
                Visualize::debugFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
                std::format(
                    Visualize::debugFormat.data(),
                    Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                    title,
                    content
                )
        };
    }
}
