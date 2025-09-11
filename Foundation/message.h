#pragma once
#include "framework.h"
#include "pch.h"

#include "entry.h"
#include "shared_container_base.h"

namespace HYDRA15::Foundation::expressman
{
    struct message_item
    {
        size_t id;
        std::string title;
        archivist::entry detail;
        std::function<void(const message_item&)> callback;
    };

    using message = std::shared_ptr<message_item>;
    using msg_list = std::list<message>;

    // 线程安全的消息队列
    // 提供单消息操作和批量消息操作
    class msg_queue :protected labourer::shared_container_base<msg_list, std::mutex>
    {
        std::condition_variable cv;

    public:
        void push(message msg);
        void push(msg_list msgs);

        message pop();
        message try_pop();
        msg_list pop_all();

        size_t size();
        bool empty();

        void clear();

    };
}