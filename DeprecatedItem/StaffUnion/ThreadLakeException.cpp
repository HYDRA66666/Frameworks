#include "pch.h"
#include "ThreadLakeException.h"

namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	ThreadLake::ThreadLake(const std::string& desp, const Foundation::iExceptionCode& code) noexcept
		: Foundation::iExceptionBase(desp, Foundation::LibInfomation::libID.StaffUnion, code)
	{
	}

	ThreadLake ThreadLake::make_exception(unsigned int exptCode)
	{
		return ThreadLake(
			visualize.thrdLakeExpt.data(),
            exptCode
		);
	}

	ThreadLake ThreadLake::TaskQueueFull() noexcept
	{
		return ThreadLake(
			visualize.thrdLakeQueueFull.data(),
            iExptCodes.threadQueueFull
		);
	}




}
