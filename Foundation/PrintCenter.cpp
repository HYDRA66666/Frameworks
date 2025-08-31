#include "pch.h"
#include "PrintCenter.h"

namespace HYDRA15::Foundation::Secretary
{
    PrintCenter::PrintCenter()
        :Labourer::Background(1),
        logFile(
            std::format(
                cfg.fileNameFormat.data(), Assistant::DateTime::now_date_time("%Y-%m-%d")
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
        sleepcv.notify_all();
        wait_for_end();
        if (logFile.is_open())
            logFile.close();
    }

    void PrintCenter::clear_bottom_msg()
    {
        std::cout << "\033[2K\r";
    }

    std::string PrintCenter::print_rolling_msg()
    {
        {   // 交换缓冲区
            std::lock_guard lg(rollMsgLock);
            RollingMsgList* temp = pRollMsgLstFront;
            pRollMsgLstFront = pRollMsgLstBack;
            pRollMsgLstBack = temp;
        }

        std::string str;
        for (const auto& msg : *pRollMsgLstBack) {
            // 如果尾部有换行符，则直接输出，否则补一个换行符
            if (msg.back() == '\n')
                str.append(msg);
            else
                str.append(msg + '\n');
        }
        pRollMsgLstBack->clear();

        return str;
    }

    std::string PrintCenter::print_bottom_msg()
    {
        std::string str;
        std::list<ID> timeoutList;
        size_t other = 0;

        {
            std::lock_guard lg(btmMsgTab.lock);
            TimePiont now = TimePiont::clock::now();

            bool first = true;
            for (auto& [id, msgCtrl] : btmMsgTab)
            {
                std::lock_guard lg(msgCtrl.lock);
                if (msgCtrl.content.empty())
                {
                    other++;
                    continue;
                }
                if (now - msgCtrl.lastUpdate < cfg.btmMsgDispTimeout)    // 未超时，展示
                    if (str.size() + msgCtrl.content.size() < cfg.maxBtmChars)
                    {
                        if (!first)
                            str.append(", ");
                        if (msgCtrl.content.back() == '\n')
                            str.append(msgCtrl.content.erase(msgCtrl.content.back()));
                        else
                            str.append(msgCtrl.content);
                    }
                    else
                        other++;
                else
                    other++;
                first = false;
                if (now - msgCtrl.lastUpdate > cfg.btmMsgExistTimeout)  // 超时删除
                    timeoutList.push_back(id);
            }
        }
        
        if(other)
            str.append(std::format(cfg.otherBtmMsgFormat, other));
        
        if (!timeoutList.empty())
            for (const auto& id : timeoutList)
                btmMsgTab.unregist(id);

        return str;
    }

    std::string PrintCenter::print_file_msg()
    {
        {
            std::lock_guard lg(fileMsgLock);
            FileMsgList* temp = pFMsgLstBack;
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


    void PrintCenter::work(Background::ThreadInfo&)
    {
        while (
            working || // 工作中
            !pRollMsgLstBack->empty() || !pRollMsgLstFront->empty() || // 滚动消息不为空
            btmMsgTab.size() > 0 || // 底部消息不为空
            !pFMsgLstBack->empty() || !pFMsgLstFront->empty() // 文件消息不为空
            )
        {
            std::unique_lock lg(sleeplock);

            // 无工作，等待
            while (
                working && // 工作中
                pRollMsgLstFront->empty() && pRollMsgLstBack->empty() && // 滚动消息为空
                (TimePiont::clock::now() - lastBtmRefresh < cfg.btmMsgRefreshInterval) && // 底部刷新未到时
                pFMsgLstBack->empty() && pFMsgLstFront->empty() && // 文件消息为空
                (TimePiont::clock::now() - lastFileRefresh < cfg.fileRefreshTime) // 文件写入未到时间
                )
                sleepcv.wait(lg);

            // 检查是否需要刷新底部消息
            bool refreshBtm = false;
            if (!pRollMsgLstFront->empty() || TimePiont::clock::now() - lastBtmRefresh > cfg.btmMsgRefreshInterval)
                refreshBtm = true;

            // 清除底部消息
                clear_bottom_msg();

            // 输出滚动消息
            if (!pRollMsgLstFront->empty())
                std::cout << print_rolling_msg();

            // 输出底部消息
            if (btmMsgTab.size() > 0 && refreshBtm)
            {
                std::string a = print_bottom_msg();
                std::cout << a;
                lastBtmRefresh = TimePiont::clock::now();
            }

            std::cout.flush();

            // 输出文件消息
            if (logFile.is_open())
            {
                if (!pFMsgLstFront->empty())
                    logFile << print_file_msg();
                if (TimePiont::clock::now() - lastFileRefresh >= cfg.fileRefreshTime)
                {
                    logFile.flush();
                    lastFileRefresh = TimePiont::clock::now();
                }
            }
        }
    }

    void PrintCenter::notify()
    {
        sleepcv.notify_all();
    }

    size_t PrintCenter::rolling(const std::string& content)
    {
        std::lock_guard lg(rollMsgLock);
        pRollMsgLstFront->push_back(content);
        return rollMsgCount++;
    }

    PrintCenter::ID PrintCenter::new_bottom(int token)
    {
        try
        {
            return btmMsgTab.regist({ token ,TimePiont::clock::now() , std::string() });
        }
        catch(Exceptions::Archivist& e)
        {
            if (e.exptCode == Exceptions::Archivist::iExceptionCodes::registryTabletFull)
                throw Exceptions::Secretary::PrintCenterBtmMsgFull();
            else throw e;
        }
    }

    void PrintCenter::update_bottom(ID id, int token, const std::string& content)
    {
        BottomControlBlock* pMsgCtrl;

        try
        {
            pMsgCtrl = &btmMsgTab.find(id);
        }
        catch (Exceptions::Archivist& e)
        {
            if (e.exptCode == Exceptions::Archivist::iExceptionCodes::registryKeyNotFound)
                throw Exceptions::Secretary::PrintCenterBtmMsgNotFound();
            else throw e;
        }

        if (pMsgCtrl->token != token)
            throw Exceptions::Secretary::PrintCenterBtmMsgBadToken();

        std::lock_guard lg(pMsgCtrl->lock);
        pMsgCtrl->content = content;
        pMsgCtrl->lastUpdate = TimePiont::clock::now();
    }

    bool PrintCenter::check_bottom(ID id)
    {
        return btmMsgTab.contains(id);
    }

    bool PrintCenter::remove_bottom(ID id, int token)
    {
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

    PrintCenter::BottomControlBlock& PrintCenter::BottomControlBlock::operator=(const BottomControlBlock& src)
    {
        if (this != &src)
        {
            lastUpdate = src.lastUpdate;
            token = src.token;
            content = src.content;
        }
        return *this;
    }

    PrintCenter::BtmMsgMap::iterator PrintCenter::BtmMsgMap::begin() { return tab.begin(); }
    PrintCenter::BtmMsgMap::iterator PrintCenter::BtmMsgMap::end() { return tab.end(); }
}
