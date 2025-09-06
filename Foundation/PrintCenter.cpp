#include "pch.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::secretary
{
    PrintCenter::PrintCenter()
        :labourer::background(1),
        logFile(
            std::format(
                cfg.fileNameFormat.data(), assistant::datetime::now_date_time("%Y-%m-%d")
            ), 
            std::ios::app
            )
    {
        start();
    }

    PrintCenter& PrintCenter::get_instance()
    {
        static PrintCenter instance;
        return instance;
    }

    PrintCenter::~PrintCenter()
    {
        working = false;
        onPause = false;
        sleepcv.notify_all();
        wait_for_end();
        if (logFile.is_open())
            logFile.close();
    }

    std::string PrintCenter::clear_bottom_msg()
    {
        using namespace HYDRA15::Foundation::assistant;

        std::string str = "\r\033[2K";
        if (lastBtmLines > 1)
            str += std::string("\033[1A\033[2K") * (lastBtmLines - 1);
        lastBtmLines = 0;
        return str;
    }

    std::string PrintCenter::print_rolling_msg()
    {
        {   // 交换缓冲区
            std::lock_guard lg(rollMsgLock);
            rollmsg_list* temp = pRollMsgLstFront;
            pRollMsgLstFront = pRollMsgLstBack;
            pRollMsgLstBack = temp;
        }

        std::string str;
        for (auto& msg : *pRollMsgLstBack) {
            str.append(assistant::strip(msg) + '\n');
        }
        pRollMsgLstBack->clear();

        return str;
    }

    std::string PrintCenter::print_bottom_msg()
    {
        size_t more = 0;
        std::list<ID> expires;
        std::string str;
        bool first = true;

        std::lock_guard lk(btmMsgTabLock);
        time_point now = time_point::clock::now();
        for(auto& [id,i]: btmMsgTab)
        {
            if (i.msg.empty())
                continue;
            if(!i.neverExpire && now - i.lastUpdate > cfg.btmExpireTimeout)
            {
                expires.push_back(id);
                continue;
            }
            if (!i.forceDisplay && (now - i.lastUpdate > cfg.btmDispTimeout || lastBtmLines >= cfg.btmMaxLines))
            {
                more++;
                continue;
            }
            if(!first)
                str.append("\n");
            else
                first = false;
            str.append(assistant::strip(i.msg));
            lastBtmLines++;
        }
        if (more > 0)
        {
            if(lastBtmLines > 0)
                str.append("\n");
            str.append(std::format(cfg.btmMoreFormat.data(), more));
            lastBtmLines++;
        }

        for(const auto& id : expires)
            btmMsgTab.unregist(id);

        return str;
    }

    std::string PrintCenter::print_file_msg()
    {
        {
            std::lock_guard lg(fileMsgLock);
            filemsg_list* temp = pFMsgLstBack;
            pFMsgLstBack = pFMsgLstFront;
            pFMsgLstFront = temp;
        }

        std::string str;

        for (const auto& msg : *pFMsgLstBack)
            if (msg.back() == '\n')
                str.append(msg);
            else
                str.append(msg + '\n');
        pFMsgLstBack->clear();

        return str;
    }


    void PrintCenter::work(background::thread_info&)
    {
        while (
            working || // 工作中
            !pRollMsgLstBack->empty() || !pRollMsgLstFront->empty() || // 滚动消息不为空
            btmMsgTab.size() > 0 || // 底部消息不为空
            !pFMsgLstBack->empty() || !pFMsgLstFront->empty() // 文件消息不为空
            )
        {
            std::unique_lock lg(sleeplock);

            while(onPause) // 暂停
                sleepcv.wait(lg);

            // 无工作，等待
            while (
                working && // 工作中
                pRollMsgLstFront->empty() && pRollMsgLstBack->empty() && // 滚动消息为空
                pFMsgLstBack->empty() && pFMsgLstFront->empty() && // 文件消息为空
                (time_point::clock::now() - lastRefresh < cfg.refreshInterval) // 未到刷新时间
                )
                sleepcv.wait_for(lg, cfg.refreshInterval);

            // 清除底部消息
            std::cout << clear_bottom_msg();

            // 输出滚动消息
            if (!pRollMsgLstFront->empty())
                std::cout << print_rolling_msg();

            // 输出底部消息
            if (btmMsgTab.size() > 0)
            {
                std::cout << print_bottom_msg();
            }

            // 输出文件消息
            if (logFile.is_open())
            {
                if (!pFMsgLstFront->empty())
                    logFile << print_file_msg();
                if (time_point::clock::now() - lastFileRefresh >= cfg.fileRefreshTime)
                {
                    logFile.flush();
                    lastFileRefresh = time_point::clock::now();
                }
            }

            // 计时
            lastRefresh = time_point::clock::now();
        }
    }

    void PrintCenter::notify()
    {
        sleepcv.notify_all();
    }

    PrintCenter& PrintCenter::operator<<(const std::string& content)
    {
        rolling(content);
        file(content);
        notify();
        return *this;
    }

    void PrintCenter::pause()
    {
        onPause = true;
    }

    void PrintCenter::unpause()
    {
        onPause = false;
    }

    size_t PrintCenter::rolling(const std::string& content)
    {
        std::lock_guard lg(rollMsgLock);
        pRollMsgLstFront->push_back(content);
        return rollMsgCount++;
    }

    PrintCenter::ID PrintCenter::new_bottom(int token, bool forceDisplay, bool neverExpire)
    {
        std::lock_guard lk(btmMsgTabLock);
        try
        {
            return btmMsgTab.regist({ token ,time_point::clock::now(), forceDisplay, neverExpire, std::string() });
        }
        catch(Exceptions::archivist& e)
        {
            if (e.exptCode == Exceptions::archivist::iException_codes::registryTabletFull)
                throw Exceptions::secretary::PrintCenterBtmMsgFull();
            else throw e;
        }
    }

    void PrintCenter::update_bottom(ID id, int token, const std::string& content)
    {
        btmmsg_ctrlblock* pMsgCtrl;
        std::lock_guard lk(btmMsgTabLock);

        try
        {
            pMsgCtrl = &btmMsgTab.find(id);
        }
        catch (Exceptions::archivist& e)
        {
            if (e.exptCode == Exceptions::archivist::iException_codes::registryKeyNotFound)
                throw Exceptions::secretary::PrintCenterBtmMsgNotFound();
            else throw e;
        }

        if (pMsgCtrl->token != token)
            throw Exceptions::secretary::PrintCenterBtmMsgBadToken();

        pMsgCtrl->msg = content;
        pMsgCtrl->lastUpdate = time_point::clock::now();
    }

    bool PrintCenter::check_bottom(ID id)
    {
        std::lock_guard lk(btmMsgTabLock);
        return btmMsgTab.contains(id);
    }

    bool PrintCenter::remove_bottom(ID id, int token)
    {
        std::lock_guard lk(btmMsgTabLock);

        if (!btmMsgTab.contains(id))
            return true;

        if (btmMsgTab.find(id).token != token)
            return false;

        return btmMsgTab.unregist(id);
    }

    size_t PrintCenter::file(const std::string& content)
    {
        std::lock_guard lg(fileMsgLock);

        pFMsgLstFront->push_back(content);
        return fileMsgCount++;
    }
}
