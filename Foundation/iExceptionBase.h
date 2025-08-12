#pragma once
#include "pch.h"
#include "framework.h"

#include "Infomation.h"


namespace HYDRA15::Frameworks::Foundation
{
	// 异常处理的基础
	// 相比标准库异常，额外记录了：
	//    - 描述字符串
	//    - 异常信息
	class iExceptionBase :public std::exception
	{
		StaticString baseWhatStrFormat = "iException: {0} ( 0x{1:08X} : 0x{2:08X} )\n";

	protected:
		// 记录的信息
		const Infomation exptInfo;
		const std::string description;

		// what字符串缓存
		mutable std::string whatStr;

	public:
		// 构造和析构
		iExceptionBase() noexcept = delete;
		iExceptionBase(const std::string& desp, const Infomation& info = {}) noexcept;
		virtual ~iExceptionBase() noexcept = default;

		// what()
		virtual const char* what() const noexcept override;

		// 获取和写入信息
		const Infomation& getExptInfo() const noexcept;
		const std::string& getDescription() const noexcept;


		// 启用栈跟踪支持
#ifdef LIB_IEXPT_STACKTRACE_ENABLE
	private:
		std::stacktrace stackTrace;
		StaticString baseStackTraceFormat = "Stack Trace: \n{0}";
	public:
		const std::stacktrace& getStackTrace() const noexcept;
#endif // LIB_IEXPT_STACKTRACE_ENABLE
	};
}