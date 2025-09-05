﻿#include "pch.h"
#include "background.h"

namespace HYDRA15::Foundation::labourer
{
    void background::work_shell(thread_info& info)
    {
        info.thread_state = thread_info::state::undefined;
        // 等待所有线程准备就绪
        checkpoint.arrive_and_wait();
        // 执行工作
        work(info);
        info.thread_state = thread_info::state::finishing;
        // 等待所有线程完成工作
        auto t = checkpoint.arrive();
    }

    void background::start()
    {
        auto t = checkpoint.arrive();
    }

    void background::wait_for_end()
    {
        checkpoint.arrive_and_wait();
    }

    background::background(unsigned int bkgThrCount)
        : checkpoint(bkgThrCount + 1)
    {
        threads.resize(bkgThrCount);
        for (auto& i : threads)
            i.thread = std::make_shared<std::thread>(&background::work_shell, this, std::ref(i.info));
        for (auto& item : threads)
            item.thread->detach();
    }

    background::background()
        :background(1)
    {
    }

    background::iterator::iterator(list_iter iter)
        :it(iter)
    {

    }

    background::iterator& background::iterator::operator++()
    {
        it++;
        return *this;
    }

    bool background::iterator::operator!=(const iterator& other) const
    {
        return it != other.it;
    }

    background::thread_info& background::iterator::operator*() const
    {
        return it->info;
    }

    background::iterator background::begin()
    {
        return iterator(threads.begin());
    }

    background::iterator background::end()
    {
        return iterator(threads.end());
    }
}