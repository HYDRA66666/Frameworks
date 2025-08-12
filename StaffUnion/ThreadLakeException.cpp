#include "pch.h"
#include "ThreadLakeException.h"

namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	ThreadLakeException::ThreadLakeException(const std::string& desp, const Foundation::Infomation& info) noexcept
		: Foundation::iExceptionBase(desp, info)
	{
	}

	ThreadLakeException ThreadLakeException::makeException(unsigned int exptCode)
	{
		return ThreadLakeException(
			visualize.thrdLakeExpt.data(),
			{ iExptCodes.libID, exptCode, 0, 0, nullptr, nullptr }
		);
	}

	ThreadLakeException ThreadLakeException::makeQueueFullException() noexcept
	{
		return ThreadLakeException(
			visualize.thrdLakeQueueFull.data(),
			{ iExptCodes.libID, iExptCodes.threadQueueFull, 0, 0, nullptr, nullptr }
		);
	}




}
