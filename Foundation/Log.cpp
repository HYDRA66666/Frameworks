#include "pch.h"
#include "Log.h"

namespace HYDRA15::Foundation::Secretary
{
    void Log::log(const std::string& title, const std::string& content)
    {
        PrintCenter::get_instance().rolling(
            std::format(
                Visualize::logFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
        PrintCenter::get_instance().file(
            std::format(
                Visualize::logFormat.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
    }

    void Log::warning(const std::string& title, const std::string& content)
    {
        PrintCenter::get_instance().rolling(
            std::format(
                Visualize::warningFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
        PrintCenter::get_instance().file(
            std::format(
                Visualize::warningFormat.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
    }

    void Log::error(const std::string& title, const std::string& content)
    {
        PrintCenter::get_instance().rolling(
            std::format(
                Visualize::errorFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
        PrintCenter::get_instance().file(
            std::format(
                Visualize::errorFormat.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
    }

    void Log::debug(const std::string& title, const std::string& content)
    {
        PrintCenter::get_instance().rolling(
            std::format(
                Visualize::debugFormatClr.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
        PrintCenter::get_instance().file(
            std::format(
                Visualize::debugFormat.data(),
                Assistant::DateTime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            )
        );
    }
}
