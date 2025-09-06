#include "pch.h"
#include "utility.h"

namespace HYDRA15::Foundation::assistant
{
    std::string operator*(std::string str, size_t count) {
        std::string result;
        result.reserve(str.size() * count);
        for (size_t i = 0; i < count; ++i) {
            result += str;
        }
        return result;
    }

    std::string& strip(std::string& str)
    {
        size_t pos = 0;
        while (pos < str.size())
            if (str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n' || str[pos] == '\r' || str[pos] == '\0')
                pos++;
            else
                break;
        str.erase(0, pos);

        pos = str.size() - 1;
        while (pos > 0)
            if (str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n' || str[pos] == '\r' || str[pos] == '\0')
                pos--;
            else
                break;
        str.erase(pos + 1);

        return str;
    }
}