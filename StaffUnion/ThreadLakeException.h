#pragma once
#include "pch.h"
#include "framework.h"

#include "Foundation/Infomation.h"
#include "Foundation/iExceptionBase.h"
#include "iExceptionInfomation.h"


namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	// 线程池异常
	class ThreadLake : public Foundation::iExceptionBase
	{
		static struct Visualize
		{
			StaticString thrdLakeExpt = "ThreadLake Exception";

			StaticString thrdLakeQueueFull = "ThreadLake: Task queue is full.";
		}visualize;

	public:
		ThreadLake(
			const std::string& desp = visualize.thrdLakeExpt.data(),
			const Foundation::Infomation& info = {}
		) noexcept;
		ThreadLake() = delete;
		virtual ~ThreadLake() noexcept = default;


		// 快速创建异常
		static ThreadLake makeException(unsigned int exptCode);

		static ThreadLake TaskQueueFullException() noexcept;
	};
}