#pragma once
#include "pch.h"
#include "framework.h"

#include "Foundation/Infomation.h"
#include "Foundation/iExceptionBase.h"
#include "iExceptionInfomation.h"


namespace HYDRA15::Frameworks::StaffUnion::iExceptions
{
	// �̳߳��쳣
	class ThreadLakeException : public Foundation::iExceptionBase
	{
		static struct Visualize
		{
			StaticString thrdLakeExpt = "ThreadLake Exception";

			StaticString thrdLakeQueueFull = "ThreadLake: Task queue is full.";
		}visualize;

	public:
		ThreadLakeException(
			const std::string& desp = visualize.thrdLakeExpt.data(),
			const Foundation::Infomation& info = {}
		) noexcept;
		ThreadLakeException() = delete;
		virtual ~ThreadLakeException() noexcept = default;


		// ���ٴ����쳣
		static ThreadLakeException makeException(unsigned int exptCode);

		static ThreadLakeException makeQueueFullException() noexcept;
	};
}