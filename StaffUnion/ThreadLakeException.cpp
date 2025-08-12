#include "pch.h"
#include "ThreadLakeException.h"

namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	ThreadLake::ThreadLake(const std::string& desp, const Foundation::Infomation& info) noexcept
		: Foundation::iExceptionBase(desp, info)
	{
	}

	ThreadLake ThreadLake::makeException(unsigned int exptCode)
	{
		return ThreadLake(
			visualize.thrdLakeExpt.data(),
			{ iExptCodes.libID, exptCode, 0, 0, nullptr, nullptr }
		);
	}

	ThreadLake ThreadLake::TaskQueueFullException() noexcept
	{
		return ThreadLake(
			visualize.thrdLakeQueueFull.data(),
			{ iExptCodes.libID, iExptCodes.threadQueueFull, 0, 0, nullptr, nullptr }
		);
	}




}
