#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Foundation
{

	// ���ڽ�����Ϣ��һ���׼��������  
	class Infomation
	{
	public:
		unsigned int type = 0;
		unsigned int subType = 0;
		long long int paramInt1 = 0;
		long long int paramInt2 = 0;
		void* paramPointer1 = nullptr;
		void* paramPointer2 = nullptr;
	};

}