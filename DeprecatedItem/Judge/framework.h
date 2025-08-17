#pragma once

// 此库包含错误处理流程相关内容
// 主要内容：
//   - iException：用于错误处理流程的、封装的异常信息
//   - iExceptionManager：异常处理器


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


// 常用类型定义
#define StaticString static constexpr std::string_view
#define StaticUInt static constexpr unsigned int