﻿#pragma once
#include "pch.h"
#include "framework.h"

#include "Background.h"
#include "ThreadLakeException.h"


namespace HYDRA15::Frameworks::StaffUnion
{

    // 线程池
    class ThreadLake :Background
    {
        // 任务和任务包定义
    public:
        template<typename ReturnType = void>
        using Task = std::function<ReturnType()>;
        struct TaskPackage
        {
            Task<> task;
            Task<> callback;	// 任务完成后的回调
        };

        //任务队列
    private:
		std::queue <TaskPackage> taskQueue; //任务队列
        const size_t tskQueMaxSize = 0; //任务队列最大大小，0表示无限制
		std::mutex queueMutex;
		std::condition_variable queueCv;

        //后台任务
        bool working = false;
        virtual void work(Background::ThreadInfo& info) override;

        //接口
    public:
        ThreadLake(int threadCount = 10, size_t tskQueMaxSize = 0);
        ThreadLake() = delete;
        ~ThreadLake();

        //提交任务
        
		// 方法1：提交任务函数 std::function 和回调函数 std::function，推荐使用此方法
        template<typename ReturnType>
        auto submit(Task<ReturnType>& task, Task<> callback = Task<>())
            -> std::future<ReturnType>
        {
            auto pkgedTask = std::make_shared<std::packaged_task<ReturnType()>>(task);

            // 插入任务包
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // 队列已满
                {
                    throw iExceptions::ThreadLake::TaskQueueFullException();
                }

                taskQueue.push(
                    {
                        Task<>([pkgedTask] { (*pkgedTask)(); }),
                        callback
                    }
                );
                queueCv.notify_one();
            }

            return pkgedTask->get_future();
        }

        //方法2：直接提交任务包
        void submit(const TaskPackage& taskPkg);

        // 方法3：提交裸函数指针和参数，不建议使用此方法，仅留做备用
        template<typename F, typename ... Args>
        auto submit(F&& f, Args &&...args)
            -> std::future<typename std::invoke_result<F, Args...>::type>
        {
            using return_type = typename std::invoke_result<F, Args...>::type;

            auto task = 
                std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );

            // 插入任务包
            {
				std::lock_guard<std::mutex> lock(queueMutex);
                if(tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // 队列已满
                {
                    throw iExceptions::ThreadLake::TaskQueueFullException();
				}
                taskQueue.push(
                    { 
                        Task<>([task] { (*task)(); }), 
                        Task<>() 
                    }
                );
                queueCv.notify_one();
            }

            return task->get_future();
        }

        

    };
}
