#include "pch.h"
#include "Background.h"

namespace HYDRA15::Frameworks::StaffUnion
{
	void Background::work_shell(ThreadInfo& info)
	{
        info.state = ThreadInfo::State::undefined;
		// 等待所有线程准备就绪
		checkpoint.arrive_and_wait();
		// 执行工作
		work(info);
        info.state = ThreadInfo::State::finishing;
		// 等待所有线程完成工作
		checkpoint.arrive();
	}

	void Background::start()
	{
		checkpoint.arrive();
	}

	void Background::wait_for_end()
	{
		checkpoint.arrive_and_wait();
	}
	
	Background::Background(unsigned int bkgThrCount) 
		: checkpoint(bkgThrCount + 1)
	{
		threads.resize(bkgThrCount);
		for (auto& i :threads)
            i->thread = std::thread(&Background::work_shell, this, std::ref(i->info));
		for (auto& item : threads)
            item->thread.detach();
	}

    Background::iterator::iterator(list_iter iter)
        :it(iter)
    {

    }

    Background::iterator& Background::iterator::operator++()
    {
        ++it;
        return *this;
    }

    bool Background::iterator::operator!=(const iterator& other) const
    {
        return it != other.it;
    }

    Background::ThreadInfo& Background::iterator::operator*() const
    {
        return (*it)->info;
    }

    Background::iterator Background::begin()
    {
        return iterator(threads.begin());
    }

    Background::iterator Background::end()
    {
        return iterator(threads.end());
    }
}