#pragma once
#include "pch.h"
#include "framework.h"

#include "iExceptionBasicHandler.h"

namespace HYDRA15::Frameworks::Foundation
{
	// ��Ҫ����ģʽ������Ӧ����
	//		- public�̳д���
	//		- ����������Ϊ��Ԫ��
	// ���ཫ���״ε��� getInstance ʱ��ʵ����
	template <class T>
	class SingletonBase
	{
		
		SingletonBase(cost SingletonBase&) = delete;
		SingletonBase& operator=(const SingletonBase&) = delete;

		virtual ~SingletonBase() = default;

	protected:
		SingletonBase() = default;

	public:
		static T& getInstance();
	};


	template <class T>
	static T& SingletonBase<T>::getInstance()
	{
		try
		{
			static T instance;
		}
		catch(const iExceptionBase&e)
		{
			iExceptionBasicHandler::handle_base_exception(e);
		}
		catch(const std::exception& e)
		{
			iExceptionBasicHandler::handle_system_exception(e);
		}

		return instance;
	}
}