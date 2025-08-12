#pragma once
#include "pch.h"
#include "framework.h"



namespace HYDRA15::Frameworks::StaffUnion::Utilities
{
	// �����������̰߳�ȫ��
	//    - ��׼���ò�ʹ���κ�������
	//    - �������������ͬʱ���У�������ý���ʱ��ֹ��ռ���ý���
	//    - ��ռ���ý���ʱ��ֹ�κ��������ý���
	//    - ��ռ���ú͹�����õ�׼��������������;���
	// ģ�������
	//   - Container: ��������
	//   - Lock: �����ͣ��������� std::mutex �Ľӿ�
	// ����ʹ��ʾ����
	//   - �����س�Ա������call(&Container::func, args...)
	//   - �����س�Ա������call(static_cast<Ret (Container::*)(Args&&...)>(&Container::func), args...)������static_cast��ָ������ָ�����صİ汾
	template<class Container, class Lock>
	class SharedContainerBase
	{
		Container container;
		Lock lock;

	public:
		virtual ~SharedContainerBase() = default;

		// ��׼����
		template<typename F, typename... Args>
		decltype(auto) call(F&& f, Args&&... args)
		{
				return std::invoke(std::forward<F>(f), container, std::forward<Args>(args)...);
		}

		template<typename F, typename... Args>
		decltype(auto) static_call(F&& f, Args&&... args)
		{
				return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
		}
		
		// �������
		template<typename F, typename... Args>
		decltype(auto) call_shared(F&& f, Args&&... args)
		{
				std::shared_lock<Lock> guard(lock);
				return std::invoke(std::forward<F>(f), container, std::forward<Args>(args)...);
		}

		template<typename F, typename... Args>
		decltype(auto) static_call_shared(F&& f, Args&&... args)
		{
				std::shared_lock<Lock> guard(lock);
				return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
		}

		// ��ռ����
		template<typename F, typename... Args>
		decltype(auto) call_unique(F&& f, Args&&... args)
		{
				std::unique_lock<Lock> guard(lock);
				return std::invoke(std::forward<F>(f), container, std::forward<Args>(args)...);
		}

		template<typename F, typename... Args>
		decltype(auto) static_call_unique(F&& f, Args&&... args)
		{
				std::unique_lock<Lock> guard(lock);
				return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
		}
	};


}