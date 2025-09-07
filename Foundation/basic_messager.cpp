#include "pch.h"
#include "basic_messager.h"

namespace HYDRA15::Foundation::expressman
{
    void basic_messager::regist(const archivist::index& idx, int token)
    {
        msgQueTab.call_unique(
            static_cast<void(msg_tab::*)(const archivist::index&, msgque_ctrlblk&&)>(&msg_tab::regist),
            idx,
            msgque_ctrlblk{ token, std::make_shared<msg_queue>() }
        );
    }

    void basic_messager::unregist(const archivist::index& idx, int token)
    {
        std::lock_guard lg(msgQueTab);

        if(!msgQueTab.call(
            static_cast<bool(msg_tab::*)(const archivist::index&)const>(&msg_tab::contains),
            idx
        ))
            throw Exceptions::expressman::MessagerIndexNotFound();

        if(msgQueTab.call(
            static_cast<msgque_ctrlblk&(msg_tab::*)(const archivist::index&)>(&msg_tab::fecth),
            idx
        ).token!=token)
            throw Exceptions::expressman::MessagerInvalidToken();

        msgQueTab.call(
            static_cast<bool(msg_tab::*)(const archivist::index&)>(&msg_tab::unregist),
            idx
        );
    }

    bool basic_messager::post(const archivist::index& idx, const message& msg)
    {
        if(!msgQueTab.call_shared(
            static_cast<bool(msg_tab::*)(const archivist::index&)const>(&msg_tab::contains),
            idx
        ))
            return false;

        msgQueTab.call_shared(
            static_cast<msgque_ctrlblk&(msg_tab::*)(const archivist::index&)>(&msg_tab::fecth),
            msg
        ).queue->push(msg);
        return true;
    }

    bool basic_messager::post(const archivist::index& idx, const msg_list& msgs)
    {
        if(!msgQueTab.call_shared(
            static_cast<bool(msg_tab::*)(const archivist::index&)const>(&msg_tab::contains),
            idx
        ))
            return false;

        msgQueTab.call_shared(
            static_cast<msgque_ctrlblk&(msg_tab::*)(const archivist::index&)>(&msg_tab::fecth),
            idx
        ).queue->push(msgs);
        return true;
    }

    message basic_messager::fetch_one(const archivist::index& idx, int token)
    {
        return fetch(idx, token)->pop();
    }

    std::shared_ptr<msg_queue> basic_messager::fetch(const archivist::index& idx, int token)
    {
        if(!msgQueTab.call_shared(
            static_cast<bool(msg_tab::*)(const archivist::index&)const>(&msg_tab::contains),
            idx
        ))
            throw Exceptions::expressman::MessagerIndexNotFound();

        auto& ctrlblk = msgQueTab.call_shared(
            static_cast<msgque_ctrlblk&(msg_tab::*)(const archivist::index&)>(&msg_tab::fecth),
            idx
        );
        if (ctrlblk.token != token)
            throw Exceptions::expressman::MessagerInvalidToken();

        return ctrlblk.queue;
    }

    bool basic_messager::contains(const archivist::index& idx)
    {
        return msgQueTab.call_shared(
            static_cast<bool(msg_tab::*)(const archivist::index&)const>(&msg_tab::contains),
            idx
        );
    }


}
