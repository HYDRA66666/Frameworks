#include "pch.h"
#include "iExceptionBase.h"


namespace HYDRA15::Foundation::referee
{
	iExceptionBase::iExceptionBase(const std::string& desp, const iException_code& id, const iException_code& code) noexcept
        :description(desp), libID(id), exptCode(code)
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
			libID,
			exptCode
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


}
