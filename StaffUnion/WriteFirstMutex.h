#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::StaffUnion::Utilities
{
	// д����������������
	//    - ʹ�� std::shared_lock ������Ϊ��ȡ������ʹ�� std::unique_lock ������Ϊд�����
	//    - ͬһʱ����������ȡ�������ڣ�����һ��д��������ڣ�д������Ͷ�ȡ��������ͬʱ����
	//    - ����д���̵߳ȴ�ʱ��ֹͣ�µĶ�ȡ�̵߳Ľ��룬�����ж�ȡ�̶߳��˳�������д���߳̽���
	//    - ������д���߳��˳��������µĶ�ȡ�߳̽���
	// ***** ����AI��д�Ĵ��룬����δ������֤ *****
	class WriteFirstMutex
	{
        std::mutex mutex;
        std::condition_variable readCond;
        std::condition_variable writeCond;
        unsigned int activeReaders = 0;
        unsigned int waitingWriters = 0;
        bool activeWriters = false;

    public:
        WriteFirstMutex() = default;
		~WriteFirstMutex() = default;

        void lock();
        void unlock();
        bool try_lock();

        void lock_shared();
        void unlock_shared();
        bool try_lock_shared();

 
        
	};
}