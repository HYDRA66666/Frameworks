#pragma once

// 此库包含注册表相关内容
// 主要内容：
//   - Regiestry：注册机模板
//   - RegistryTablet：注册表模板

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


#define StaticString static constexpr std::string_view
#define StaticUInt static constexpr unsigned int