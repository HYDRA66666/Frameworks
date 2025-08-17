#pragma once
#include "pch.h"
#include "framework.h"

namespace HYDRA15::Foundation::Assistant
{
	// 需要单例模式的子类应当：
	//		- public继承此类
	//		- 将此类声明为友元类
	// 子类将在首次调用 getInstance 时被实例化
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