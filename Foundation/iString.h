#pragma once
#include "framework.h"
#include "pch.h"

namespace HYDRA15::Foundation::Assistant
{
    // 自动管理编码的字符串类
    // 内部使用std::wstring存储数据
    class iString : public std::wstring
    {
        // 构造与析构
    public:
        iString() = default;
        ~iString() = default;

        // 直接从宽字符串构造
        iString(const wchar_t* src);
        iString& operator=(const wchar_t* src);
        iString(const std::wstring& src);
        iString& operator=(const std::wstring& src);

        // 输入输出
    public:
        iString& encode(std::string src, int code);
        std::string decode(int code) const;
    };

}