#pragma once
#include "pch.h"
#include "framework.h"

#include "Infomation.h"


namespace HYDRA15::Frameworks::Foundation
{
	// �쳣����Ļ���
	// ��ȱ�׼���쳣�������¼�ˣ�
	//    - �����ַ���
	//    - �쳣��Ϣ
	class iExceptionBase :public std::exception
	{
		StaticString baseWhatStrFormat = "iException: {0} ( 0x{1:08X} : 0x{2:08X} )\n";

	protected:
		// ��¼����Ϣ
		const Infomation exptInfo;
		const std::string description;

		// what�ַ�������
		mutable std::string whatStr;

	public:
		// ���������
		iExceptionBase() noexcept = delete;
		iExceptionBase(const std::string& desp, const Infomation& info = {}) noexcept;
		virtual ~iExceptionBase() noexcept = default;

		// what()
		virtual const char* what() const noexcept override;

		// ��ȡ��д����Ϣ
		const Infomation& getExptInfo() const noexcept;
		const std::string& getDescription() const noexcept;


		// ����ջ����֧��
#ifdef LIB_IEXPT_STACKTRACE_ENABLE
	private:
		std::stacktrace stackTrace;
		StaticString baseStackTraceFormat = "Stack Trace: \n{0}";
	public:
		const std::stacktrace& getStackTrace() const noexcept;
#endif // LIB_IEXPT_STACKTRACE_ENABLE
	};
}