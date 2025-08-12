#pragma once
#include "pch.h"
#include "framework.h"

#include "Background.h"
#include "TaskPackage.h"
#include "ThreadLakeException.h"


namespace HYDRA15::Frameworks::StaffUnion
{
    // �̳߳�
    class ThreadLake :Background
    {

        //�������
    private:
		std::queue <TaskPackage> taskQueue; //�������
        const size_t tskQueMaxSize = 0; //�����������С��0��ʾ������
		std::mutex queueMutex;
		std::condition_variable queueCv;

        //��̨����
        bool working = false;
        void work() override;

        //�ӿ�
    public:
        ThreadLake(int threadCount = 10, size_t tskQueMaxSize = 0);
        ThreadLake() = delete;
        ~ThreadLake();

        //�ύ����
        
		// ����1���ύ������ std::packaged_task �ͻص����� std::function���Ƽ�ʹ�ô˷������������ύ����֮ǰ���л�ȡ std::future
        template<typename ReturnType>
        auto submit(std::packaged_task<ReturnType()>& task, std::function<void()> callback = std::function<void()>())
            -> std::future<ReturnType>
        {
            auto pkgedTask = std::make_shared<std::packaged_task<ReturnType()>>(std::move(task));

            // ���������
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // ��������
                {
                    throw iExceptions::ThreadLakeException::makeQueueFullException();
                }

                taskQueue.push(
                    { 
                        std::function<void()>([pkgedTask] { (*pkgedTask)(); }),
                        callback 
                    }
                )��
                queueCv.notify_one();
            }

            return pkgedTask->get_future();
        }

        //����2��ֱ���ύ�����
        void submit(TaskPackage& taskPkg);

        // ����3���ύ�㺯��ָ��Ͳ�����������ʹ�ô˷���������������
        template<typename F, typename ... Args>
        auto submit(F&& f, Args &&...args)
            -> std::future<typename std::invoke_result<F, Args...>::type>
        {
            using return_type = typename std::invoke_result<F, Args...>::type;

            auto task = 
                std::make_shared<std::packaged_task<return_type()>>(
                    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );

            // ���������
            {
				std::lock_guard<std::mutex> lock(queueMutex);
                if(tskQueMaxSize != 0 && taskQueue.size() >= tskQueMaxSize) // ��������
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
