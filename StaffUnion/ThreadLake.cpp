#include "pch.h"
#include "ThreadLake.h"

namespace HYDRA15::Frameworks::StaffUnion
{
	void ThreadLake::work()
	{
		TaskPackage taskPkg;

		while (true)
		{
			// ȡ����
			{
				std::unique_lock<std::mutex> lock(queueMutex);
				if (working && taskQueue.empty())
					queueCv.wait(lock, [this] { return !taskQueue.empty() || !working; });
				if (!working)	// ��������������˳�ѭ��
					return;
				taskPkg = std::move(taskQueue.front());
				taskQueue.pop();
			}

			// ִ������
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
		queueCv.notify_all(); // ֪ͨ���еȴ����߳�
		wait_for_end(); // �ȴ������߳̽���
	}

	void ThreadLake::submit(TaskPackage& taskPkg)
	{
		if(tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // ��������
		{
			throw iExceptions::ThreadLake::TaskQueueFullException();
		}
		std::lock_guard<std::mutex> lock(queueMutex);
		taskQueue.push(taskPkg);
		queueCv.notify_one(); // ֪ͨһ���ȴ����߳�
	}
}
