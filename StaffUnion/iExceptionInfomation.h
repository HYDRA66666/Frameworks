#pragma once
#include "pch.h"
#include "framework.h"

#include "Foundation/iExceptionBaseInfomation.h"


namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	// 异常代码
	static struct iExceptionCodes
	{
		// 线程池
		iExceptionCode threadLake = 0xA00;
		iExceptionCode threadQueueFull = 0xA01;
	} iExptCodes;
}