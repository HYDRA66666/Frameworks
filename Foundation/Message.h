#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Foundation
{
	// ���ڽ�����Ϣ��һ���׼������Ϣ�ṹ
	class Message
	{
	public:
		int type = 0;
		int subType = 0;

		std::string title;
		std::string content;


	};
}