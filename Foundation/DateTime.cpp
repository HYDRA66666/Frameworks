#include "pch.h"
#include "DateTime.h"

namespace HYDRA15::Foundation::Assistant
{
    extern int localTimeZone = 8;

    DateTime::DateTime()
        :stamp(std::time(NULL))
    { }

    DateTime::DateTime(time_t t)
        :stamp(t)
    { }

    std::string DateTime::date_time(std::string format, int timeZone) const
    {
        if(timeZone < -12 || timeZone > 14)
            throw Exceptions::Assistant::DateTimeInvalidTimeZone();

        time_t localStamp = stamp + timeZone * 3600;
        tm local;
        gmtime_s(&local, &localStamp);
        std::string str;
        str.resize(format.size() * 2 + 20, '\0');
        size_t len = strftime(str.data(), str.size(), format.data(), &local);
        str.resize(len);
        return str;
    }

    DateTime DateTime::now()
    {
        return DateTime();
    }

    std::string DateTime::now_date_time(std::string format, int timeZone)
    {
        return DateTime().date_time(format, timeZone);
    }
}