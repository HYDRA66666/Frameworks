#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::StaffUnion
{
	// �̳д�������ཫ�ڳ�ʼ��ʱ�Զ������趨�Ĳ���������̨�߳�
	// ʹ�÷�����
	//   - ��д work() ����
	//   - ���캯����ָ���̲߳���
	//   - �����ʼ����ɺ���� start() ���������߳�
    //   - ������������Ҫ����֪ͨ�����߳̽������񲢷���
	//   - ������������� stop() �����ȴ��̷߳��أ������̶߳����غ�˺���������
	// �̵߳�����һ����ʼ���󲻿ɸ��ģ���Ҫ��̬�����߳��������鴴����� Background ʵ��
    class Background
    {

        std::barrier<> checkpoint;  //�����ͽ���ͬ��
        std::list<std::shared_ptr<std::thread>> threads; // �첽�߳���
		void work_shell(); // ��װ�����������ͬ���Ĺ�������

    public:
        virtual void work() = 0;  // ��д�˷������첽ִ��

        // ����ͬ���ͽ���ͬ��
        void start();
        void wait_for_end();

        // ���캯��������Ϊ�첽�߳�������Ĭ��Ϊ1
        Background(int bkgThrCount);
        Background();
		virtual ~Background() = default;
		Background(const Background&) = delete;
		Background& operator=(const Background&) = delete;
    };

}
