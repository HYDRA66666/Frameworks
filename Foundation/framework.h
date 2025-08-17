#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


// 常用类型定义
#define StaticString static constexpr std::string_view
#define StaticUInt static constexpr unsigned int




// 自定义配置内容

// 库默认输出流
// 例如用于日志输出、错误信息输出
#define lib_default_ostream(str) \
	std::cout << str

// 启用栈跟踪支持
// 启用可能会影响安全性和性能
#define LIB_IEXPT_STACKTRACE_ENABLE 
