#include "pch.h"
#include "Background.h"

namespace HYDRA15::Frameworks::StaffUnion
{
	void Background::work_shell()
	{
		// �ȴ������߳�׼������
		checkpoint.arrive_and_wait();
		// ִ�й���
		work();
		// �ȴ������߳���ɹ���
		checkpoint.arrive();
	}

	void Background::start()
	{
		checkpoint.arrive();
	}

	void Background::wait_for_end()
	{
		checkpoint.arrive_and_wait();
	}
	
	Background::Background(unsigned int bkgThrCount) 
		: checkpoint(bkgThrCount + 1)
	{
		threads.resize(bkgThrCount);
		for (auto& i :threads)
			i = std::make_shared<std::thread>(&Background::work_shell, this);
		for (auto& item : threads)
			item->detach();
	}
}