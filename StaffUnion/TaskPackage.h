#pragma once
#include "pch.h"
#include "framework.h"

namespace HYDRA15::Frameworks::StaffUnion
{
	using Task = std::function<void()>;
	struct TaskPackage
	{
		Task task;
		Task callback;	// ������ɺ�Ļص�
	};
}