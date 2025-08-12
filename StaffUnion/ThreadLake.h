#pragma once
#include "pch.h"
#include "framework.h"

#include "Background.h"
#include "TaskPackage.h"
#include "ThreadLakeException.h"


namespace HYDRA15::Frameworks::StaffUnion
{
    // 线程池
    class ThreadLake :Background
    {

        //任务队列
    private:
		std::queue <TaskPackage> taskQueue; //任务队列
        const size_t tskQueMaxSize = 0; //任务队列最大大小，0表示无限制
		std::mutex queueMutex;
		std::condition_variable queueCv;

        //后台任务
        bool working = false;
        void work() override;

        //接口
    public:
        ThreadLake(int threadCount = 10, size_t tskQueMaxSize = 0);
        ThreadLake() = delete;
        ~ThreadLake();

        //提交任务
        
		// 方法1：提交任务函数 std::packaged_task 和回调函数 std::function，推荐使用此方法，建议在提交任务之前自行获取 std::future
        template<typename ReturnType>
        auto submit(std::packaged_task<ReturnType()>& task, std::function<void()> callback = std::function<void()>())
            -> std::future<ReturnType>
        {
            auto pkgedTask = std::make_shared<std::packaged_task<ReturnType()>>(std::move(task));

            // 插入任务包
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // 队列已满
                {
                    throw iExceptions::ThreadLakeException::makeQueueFullException();
                }

                taskQueue.push(
                    { 
                        std::function<void()>([pkgedTask] { (*pkgedTask)(); }),
                        callback 
                    }
                )；
                queueCv.notify_one();
            }

            return pkgedTask->get_future();
        }

        //方法2：直接提交任务包
        void submit(TaskPackage& taskPkg);

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
                    throw iExceptions::ThreadLakeException::makeQueueFullException();
				}
                taskQueue.push(
                    { 
                        std::function<void()>([task] { (*task)(); }), 
                        std::function<void()>() 
                    }
                );
                queueCv.notify_one();
            }

            return task->get_future();
        }

        

    };
}
