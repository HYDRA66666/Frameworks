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

    std::string& strip(std::string& str, std::function<bool(char)> is_valid)
    {
        size_t pos = 0;
        while (pos < str.size())
        {
            if (is_valid(str[pos]))
                break;
            pos++;
        }
        str.erase(0, pos);

        pos = str.size() - 1;
        while (pos > 0)
        {
            if (is_valid(str[pos]))
                break;
            pos--;
        }
        str.erase(pos + 1);

        return str;
    }

    std::string hex_heap(unsigned char* pBegin, unsigned int size, unsigned int preLine)
    {
        std::string str = "   -------- Hex Heap --------   \n";
        str.reserve((preLine * 0x4 + 0x20) * (size / preLine + 1) + 0x100);

        // 打印表头
        str += "          ";
        for (unsigned int i = 0; i < preLine; i++)
            str += std::format("{:02X} ", i);
        str += "\n\n";

        // 打印数据
        std::string dataStr, charStr;
        dataStr.reserve(preLine * 3);
        charStr.reserve(preLine);
        for (unsigned int i = 0; i < size; i++)
        {
            if (i % preLine == 0)   // 行头地址
                str += std::format("{:08X}  ", i);

            dataStr += std::format("{:02X} ", pBegin[i]);
            if (pBegin[i] >= 0x20 && pBegin[i] <= 0x7E)
                charStr += pBegin[i];
            else
                charStr += ' ';

            if ((i + 1) % preLine == 0)
            {
                str += std::format("{}  |{}| \n", dataStr, charStr);
                dataStr.clear();
                charStr.clear();
            }

            if (i == size - 1 && (i + 1) % preLine != 0)  // 最后一行对齐
            {
                dataStr += std::string("   ") * (preLine - i % preLine - 1);
                charStr += std::string(" ") * (preLine - i % preLine - 1);
                str += std::format("{}  |{}| \n", dataStr, charStr);
                dataStr.clear();
                charStr.clear();
            }
        }

        return str;
    }
}