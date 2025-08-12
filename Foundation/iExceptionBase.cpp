#include "pch.h"
#include "iExceptionBase.h"


namespace HYDRA15::Frameworks::Foundation
{
	iExceptionBase::iExceptionBase(const std::string& desp, const Infomation& info) noexcept
		:exptInfo(info), description(desp)
#ifdef LIB_IEXPT_STACKTRACE_ENABLE
		, stackTrace(std::stacktrace::current())
#endif // LIB_IEXPT_STACKTRACE_ENABLE
	{

	}

	const char* iExceptionBase::what() const noexcept
	{
		whatStr = std::format(
			baseWhatStrFormat,
			description,
			exptInfo.type,
			exptInfo.subType
		);

		// 启用栈跟踪支持
#ifdef LIB_IEXPT_STACKTRACE_ENABLE
		whatStr += std::format(
			baseStackTraceFormat,
			stackTrace
		);
#endif // LIB_IEXPT_STACKTRACE_ENABLE

		return whatStr.c_str();
	}

	const Infomation& iExceptionBase::getExptInfo() const noexcept
	{
		return exptInfo;
	}

	const std::string& iExceptionBase::getDescription() const noexcept
	{
		return description;
	}

	const std::stacktrace& iExceptionBase::getStackTrace() const noexcept
	{
		return stackTrace;
	}


}
