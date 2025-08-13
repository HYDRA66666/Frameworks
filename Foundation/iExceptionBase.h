#pragma once
#include "pch.h"
#include "framework.h"

namespace HYDRA15::Frameworks::Foundation
{
	// 异常处理的基础
	// 相比标准库异常，额外记录了：
	//    - 描述字符串
	//    - 异常信息

    using iExceptionCode = unsigned int;
	class iExceptionBase :public std::exception
	{
		StaticString baseWhatStrFormat = "iException: {0} ( 0x{1:08X} : 0x{2:08X} )\n";

	protected:
		

		// what字符串缓存
		mutable std::string whatStr;

	public:
        // 记录的信息
        const iExceptionCode libID;
        const iExceptionCode exptCode;
        const std::string description;

		// 构造和析构
		iExceptionBase() noexcept = delete;
		iExceptionBase(const std::string& desp, const iExceptionCode& id, const iExceptionCode& code) noexcept;
		virtual ~iExceptionBase() noexcept = default;

		// what()
		virtual const char* what() const noexcept override;


		// 启用栈跟踪支持
#ifdef LIB_IEXPT_STACKTRACE_ENABLE
	private:
		
		StaticString baseStackTraceFormat = "Stack Trace: \n{0}";
	public:
        const std::stacktrace stackTrace;
#endif // LIB_IEXPT_STACKTRACE_ENABLE
	};
}