#pragma once
#include "framework.h"
#include "pch.h"

#include "message.h"
#include "registry.h"
#include "index.h"
#include "shared_container_base.h"
#include "expressman_exception.h"
#include "concepts.h"

namespace HYDRA15::Foundation::expressman
{
    // 消息分发机
    // 使用方法：
    //  - 注册消息队列，以 Index 为键类型，需要提供 int 类型的 token
    //  - 提交消息，指定消息队列的 Index
    //  - 接受消息队列中的消息，或者是直接获取整个消息队列的引用，需要提供 token
    //  - 删除消息队列，需要提供 token
    class basic_messager
    {
        struct msgque_ctrlblk
        {
            int token = 0;
            std::shared_ptr<msg_queue> queue = nullptr;
        };

        using msg_tab = archivist::basic_registry<archivist::index, msgque_ctrlblk>;
        using safe_msg_tab = labourer::shared_container_base<msg_tab, std::shared_mutex>;

    private:
        safe_msg_tab msgQueTab;

    public:
        void regist(const archivist::index& idx, int token);
        void unregist(const archivist::index& idx, int token);

        bool post(const archivist::index& idx, const message& msg);
        bool post(const archivist::index& idx, const msg_list& msgs);

        message fetch_one(const archivist::index& idx, int token);
        std::shared_ptr<msg_queue> fetch(const archivist::index& idx, int token);

        bool contains(const archivist::index& idx);


    };
}   