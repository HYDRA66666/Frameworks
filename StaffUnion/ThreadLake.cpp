#include "pch.h"
#include "ThreadLake.h"

namespace HYDRA15::Frameworks::StaffUnion
{
	void ThreadLake::work()
	{
		TaskPackage taskPkg;

		while (true)
		{
			// 取任务
			{
				std::unique_lock<std::mutex> lock(queueMutex);
				if (working && taskQueue.empty())
					queueCv.wait(lock, [this] { return !taskQueue.empty() || !working; });
				if (!working)	// 如果工作结束，退出循环
					return;
				taskPkg = std::move(taskQueue.front());
				taskQueue.pop();
			}

			// 执行任务
			if (taskPkg.task)
				taskPkg.task();
			if (taskPkg.callback)
				taskPkg.callback();
		}

	}

	ThreadLake::ThreadLake(int threadCount, size_t tskQueMaxSize)
		: Background(threadCount), tskQueMaxSize(tskQueMaxSize)
	{
		working = true;
		start();
	}

	ThreadLake::~ThreadLake()
	{
		working = false;
		queueCv.notify_all(); // 通知所有等待的线程
		wait_for_end(); // 等待所有线程结束
	}

	void ThreadLake::submit(TaskPackage& taskPkg)
	{
		if(tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // 队列已满
		{
			throw iExceptions::ThreadLake::TaskQueueFullException();
		}
		std::lock_guard<std::mutex> lock(queueMutex);
		taskQueue.push(taskPkg);
		queueCv.notify_one(); // 通知一个等待的线程
	}
}
