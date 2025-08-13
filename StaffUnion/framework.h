#pragma once

// 此库包含多线程相关工具
// 主要内容：
//   - ThreadLake：线程池
//   - Background：初始化时启动的后台多线程类
//   - SharedContainerBase：线程安全的容器模板


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容


// 常用类型定义
#define StaticString static constexpr std::string_view
#define StaticUInt static constexpr unsigned int

