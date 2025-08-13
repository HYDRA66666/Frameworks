#pragma once
#include "pch.h"
#include "framework.h"

#include "Foundation/LibID.h"


namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	// 异常代码
	static struct iExceptionCodes
	{
		// 线程池
		StaticUInt threadLake = 0xA00;
		StaticUInt threadQueueFull = 0xA01;
	} iExptCodes;
}