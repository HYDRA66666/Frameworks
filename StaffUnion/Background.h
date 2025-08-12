#pragma once
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

        std::barrier<> checkpoint;  //启动和结束同步
        std::list<std::shared_ptr<std::thread>> threads; // 异步线程组
		void work_shell(); // 封装了启动与结束同步的工作函数

    public:
        virtual void work() = 0;  // 重写此方法以异步执行

        // 启动同步和结束同步
        void start();
        void wait_for_end();

        // 构造函数，参数为异步线程数量，默认为1
        Background(int bkgThrCount);
        Background();
		virtual ~Background() = default;
		Background(const Background&) = delete;
		Background& operator=(const Background&) = delete;
    };

}
