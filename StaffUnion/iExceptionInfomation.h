#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	// 异常代码
	static struct iExceptionCodes
	{
		iExceptionCode libID = 0xA1;

		// 线程池
		iExceptionCode threadLake = 0xA00;
		iExceptionCode threadQueueFull = 0xA01;
	} iExptCodes;
}