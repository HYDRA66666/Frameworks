#include "pch.h"
#include "message.h"

namespace HYDRA15::Foundation::expressman
{
    void msg_queue::push(message msg)
    {
        this->call_unique(
            static_cast<void(msg_list::*)(const message&)>(&msg_list::push_back),
            msg
        );
    }

    void msg_queue::push(msg_list msgs)
    {
        this->call_unique(
            static_cast<msg_list::iterator(msg_list::*)(msg_list::const_iterator, msg_list::iterator, msg_list::iterator)>
                (&msg_list::insert<msg_list::iterator>),
            this->call(static_cast<msg_list::iterator(msg_list::*)()>(&msg_list::end)),
            msgs.begin(), 
            msgs.end()
        );
    }

    message msg_queue::pop()
    {
        message msg = this->call_shared(
            static_cast<message&(msg_list::*)()>(&msg_list::front)
        );
        this->call_unique(
            static_cast<void(msg_list::*)()>(&msg_list::pop_front)
        );
        return msg;
    }

    msg_list msg_queue::pop_all()
    {
        msg_list msgs;
        this->call_unique(
            static_cast<void(msg_list::*)(msg_list&)>(&msg_list::swap),
            msgs
        );
        return msgs;
    }

    size_t msg_queue::size()
    {
        return this->call_shared(
            static_cast<size_t(msg_list::*)() const>(&msg_list::size)
        );
    }

    bool msg_queue::empty()
    {
        return this->call_shared(
            static_cast<bool(msg_list::*)() const>(&msg_list::empty)
        );
    }

    void msg_queue::clear()
    {
        this->call_unique(
            static_cast<void(msg_list::*)()>(&msg_list::clear)
        );
    }
}
