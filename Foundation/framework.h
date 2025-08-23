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

// Entry 类启用强制内容展示
// 启用后，Entry 的 info() 方法将强制输出数据的详细信息，要求 Entry 锁包含的实际数据类型必须支持 std::to_string(T) 操作，否则将编译出错
// 不启用，则只有在 info() 方法中列明的类型才会输出详细信息
//#define LIB_ENTRY_FORCEDISPLAYDETAIL_ENABLE
