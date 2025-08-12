#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::Foundation
{
	// 用于交换信息的一组标准化的消息结构
	class Message
	{
	public:
		int type = 0;
		int subType = 0;

		std::string title;
		std::string content;


	};
}