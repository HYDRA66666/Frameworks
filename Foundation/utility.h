#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::assistant
{
    std::string operator*(std::string str, size_t count);

    // 删除头尾的空字符，默认删除所有非可打印字符和空格
    std::string& strip(     
        std::string& str,
        std::function<bool(char)> is_valid = [](char c) {return c > 0x20 && c < 0x7F; }
    );

    // 删除字符串中所有的空字符，默认删除所有非可打印字符和空格
    std::string strip_all(  
        std::string& str,
        std::function<bool(char)> is_valid = [](char c) {return c > 0x20 && c < 0x7F; }
    );

    //向控制台输出十六进制的原始数据和对应的ascii字符
    std::string hex_heap(unsigned char* pBegin, unsigned int size, unsigned int preLine = 32);
}