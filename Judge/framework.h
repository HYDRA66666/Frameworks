#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


// 常用类型定义
#define StaticString static constexpr std::string_view
#define iExceptionCode static constexpr unsigned int