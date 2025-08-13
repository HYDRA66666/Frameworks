﻿#pragma once
#include "pch.h"
#include "framework.h"


namespace HYDRA15::Frameworks::StaffUnion
{
	// 继承此类的子类将在初始化时自动根据设定的参数启动后台线程
	// 使用方法：
	//   - 重写 work() 方法
	//   - 构造函数中指定线程参数
	//   - 子类初始化完成后调用 start() 方法启动线程
    //   - 结束工作后，需要自行通知工作线程结束任务并返回
	//   - 结束工作后调用 stop() 方法等待线程返回，所有线程都返回后此函数将返回
	// 线程的数量一经初始化后不可更改，需要动态调整线程数量建议创建多个 Background 实例
    class Background
    {
        // 线程信息块和线程物品
    public:
        class ThreadInfo
        {
        public:
            enum class State
            {
                undefined,
                idle,
                waiting,
                working,
                finishing
            }state = State::undefined;
        };

        class ThreadItem
        {
        public:
            std::thread thread; // 线程对象
            ThreadInfo info; // 线程信息
        };

    private:
        std::barrier<> checkpoint;  //启动和结束同步
        std::list<std::shared_ptr<ThreadItem>> threads; // 异步线程组
		void work_shell(ThreadInfo& info); // 封装了启动与结束同步的工作函数

    public:
        virtual void work(ThreadInfo& info) = 0;  // 重写此方法以异步执行

        // 启动同步和结束同步
    public:
        void start();
        void wait_for_end();

        // 构造函数，参数为异步线程数量，默认为1
    public:
        Background(unsigned int bkgThrCount = 1);
        Background() = delete;
		virtual ~Background() = default;
		Background(const Background&) = delete;
		Background& operator=(const Background&) = delete;

        // 迭代器访问每一个线程信息
    public:
        class iterator
        {
            using list_iter = std::list<std::shared_ptr<ThreadItem>>::iterator;
            list_iter it;
        public:
            iterator(list_iter iter);
            iterator& operator++();
            bool operator!=(const iterator& other) const;
            ThreadInfo& operator*() const;
        };

        iterator begin();
        iterator end();
    };

}
