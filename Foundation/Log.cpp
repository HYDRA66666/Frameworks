#include "pch.h"
#include "log.h"

namespace HYDRA15::Foundation::secretary
{
    log::logstr_pkg log::info(const std::string& title, const std::string& content)
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

    log::logstr_pkg log::warn(const std::string& title, const std::string& content)
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

    log::logstr_pkg log::error(const std::string& title, const std::string& content)
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

    log::logstr_pkg log::fatal(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.fatalFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
            std::format(
                vslz.fatalFormat.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
           )
        };
    }

    log::logstr_pkg log::debug(const std::string& title, const std::string& content)
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
    log::logstr_pkg log::trace(const std::string& title, const std::string& content)
    {
        return {
            std::format(
                vslz.traceFormatClr.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
            ),
            std::format(
                vslz.traceFormat.data(),
                assistant::datetime::now_date_time("%Y-%m-%d %H:%M:%S"),
                title,
                content
           )
        };
    }
}
